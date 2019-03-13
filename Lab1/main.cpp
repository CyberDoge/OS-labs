#include <iostream>
#include <vector>
#include <math.h>
#include "function/Function.h"
#include "function/Cos.h"
#include "function/Sin.h"

using namespace std;

static const string mathSymbols = "+-*/=";

vector<string> *parseStringWithFunctions(string function) {
    unsigned long i = 0;
    unsigned long start = 0;
    auto *res = new vector<string>();
    while (function[i] != '\0') {
        if (mathSymbols.find(function[i]) != string::npos) {
            res->push_back(function.substr(start, i - start));
            res->push_back(function.substr(start, i - start));
            start = i + 1;
        }
        ++i;
    }
    res->push_back(function.substr(start, i - start));
    return res;
}



double f(double x){
    return -exp(x);
}

int main() {

    double p, p0 = 1, eps = 0.00001;
    int i = 0, N = 10000;

    string function = "x+e^(x)=0";
    p = f(0);
    do{
        p0=p;
        p=f(p0);
    }while (abs(p-p0) > eps);
    cout<<p;
    //cin >> function;
    parseStringWithFunctions(function);


    return 0;
}
