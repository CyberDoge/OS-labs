#include <iostream>
#include <vector>
#include <math.h>
#include "function/Function.h"
#include "function/Cos.h"
#include "function/Sin.h"
#include "function/Exp.h"


using namespace std;

static const string mathSymbols = "+-*/";

vector<string> *parseStringWithFunctions(const string function) {
    unsigned long i = 0;
    unsigned long start = 0;
    auto *res = new vector<string>();
    while (function[i] != '\0') {
        if (mathSymbols.find(function[i]) != string::npos) {
            res->push_back(function.substr(start, i - start));
            string tmp(1, function[i]);
            res->push_back(tmp);

            start = i + 1;
        }
        ++i;
    }
    res->push_back(function.substr(start, i - start));
    return res;
}

vector<Function *> *functionFactory(const vector<string> &values) {
    vector<Function *> *result = new vector<Function *>();
    for (int i = 0; i < values.size(); i += 2) {
        if (values[i].rfind("cos", 0) == 0) {
            result->push_back(new Cos());
        } else if (values[i].rfind("sin", 0) == 0) {
            result->push_back(new Sin());
        } else if (values[i].rfind("e^", 0) == 0) {
            result->push_back(new Exp());
        } else {
            throw runtime_error("bad input");
        }
    }
    return result;
}

double f(double x, vector<Function *> functions, vector<string> symbols) {
    int r = 1;
    for (int i = 1; i < symbols.size() - 1; i += 2) {

        if (symbols[i] == "+") {
            x += functions[r]->countValue(x);
        } else if (symbols[i] == "-") {
            x -= functions[r]->countValue(x);
        }
        r++;
    }
    return functions[0]->revers(x);
    //return asin(-exp(x));
}

int main() {

    double p, p0 = 1, eps = 0.00001;
    int i = 0, N = 10000;

    string function = "cos(x)-e^(x)=0";

    vector<string> *parsed = parseStringWithFunctions(function);

    vector<Function *> *functions = functionFactory(*parsed);

    p = f(0, *functions, *parsed);
    do {
        p0 = p;
        p = f(p0, *functions, *parsed);
    } while (abs(p - p0) > eps);
    cout << p;
    //cin >> function;
    parseStringWithFunctions(function);


    return 0;
}
