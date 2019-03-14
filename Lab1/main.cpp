#include <iostream>
#include <vector>
#include <math.h>
#include "function/Function.h"
#include "function/Cos.h"
#include "function/Sin.h"
#include "function/Exp.h"
#include "function/Ln.h"


using namespace std;

Function *parseString(const string f, bool negative = false) {
    const unsigned long bracketIndex = f.rfind('(');
    if (bracketIndex == string::npos) {
        throw runtime_error("bad input");
    }

    Function *function;
    if (f.rfind("cos") != string::npos) {
        function = new Cos();
    } else if (f.rfind("sin") != string::npos) {
        function = new Sin();
    } else if (f.rfind("e^") != string::npos) {
        function = new Exp();
    } else if (f.rfind("ln") != string::npos) {
        function = new Ln();
    } else throw runtime_error("bad input");


//    function->setArg(stod(f.substr(bracketIndex, f.rfind(')'))));
    auto mulIndex = f.rfind('*');
    double k = pow(-1, negative);
    if (mulIndex != string::npos) {
        function->setK(k * stod(f.substr(mulIndex)));
    } else {
        function->setK(k);
    }
    return function;

}

vector<Function *> *functionFactory(const string &function) {
    unsigned long i = 0;
    unsigned long start = 0;
    auto *res = new vector<Function *>();
    while (function[i] != '\0') {
        if (function[i] == '+') {
            res->push_back(parseString(function.substr(start, i - start)));
            start = i + 1;
        } else if (function[i] == '-') {
            res->push_back(parseString(function.substr(start, i - start), true));
            start = i + 1;
        }
        ++i;
    }
    return res;
}

double f(double x, vector<Function *> functions) {
    for (int i = 1; i < functions.size(); i++) {
        x += functions[i]->countValue(x);
    }

    return functions[0]->revers(x);
    //return asin(-exp(x));
}

int main() {

    double p, p0, eps = 0.00001;
    int i = 0, N = 10000;

    string function = "cos(x)-e^(x)=0";


    vector<Function *> *functions = functionFactory(function);

    p = f(0, *functions);
    do {
        p0 = p;
        p = f(p0, *functions);
    } while (abs(p - p0) > eps);
    cout << p;
    //cin >> function;

    return 0;
}
