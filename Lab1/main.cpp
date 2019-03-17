#include <iostream>
#include <vector>
#include <math.h>
#include "function/Function.h"
#include "function/Cos.h"
#include "function/Sin.h"
#include "function/Exp.h"
#include "function/Ln.h"


using namespace std;

Function *parseString(const string &f) {
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
    if (mulIndex != string::npos) {
        function->setK(stod(f.substr(0, mulIndex)));
    }
    return function;

}

vector<Function *> *functionFactory(const string &function) {
    unsigned long i = function.size();
    unsigned long start = i;
    auto *res = new vector<Function *>();
    while (i != 0) {
        if (function[i] == '+' || function[i] == '-') {
            res->push_back(parseString(function.substr(i, start)));
            start = i;
        }
        --i;
    }
    res->push_back(parseString(function.substr(i, start)));

    return res;
}

double f(double x, vector<Function *> functions) {
    double res = 0;
    for (auto &function : functions) {
        res += function->countValue(x);
    }
    return res;
    //return asin(-exp(x));
}

int main() {


//    string function = "0.07*e^(x) + cos(x)=x";
    string functionStr[] = {
            "0.07*e^(x) + cos(x)=x",

    };
    int iter = 0;
    for (const auto &function : functionStr) {
        double p, p0, eps = 0.00001;
        int i = 0, N = 10000;
        try {
            vector<Function *> *functions = functionFactory(function);
            p = f(0.3, *functions);
            do {
                p0 = p;
                p = f(p0, *functions);
                i++;
            } while (abs(p - p0) > eps);
            cout << "iteration " << iter << "; res = " << p << "; i = " << i << endl;
            iter++;
        } catch (exception e) {
            cout << "bad input"<< endl;
            exit(-3);
        }
    }

    return 0;
}