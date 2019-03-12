#include <iostream>
#include <cstring>
#include "function/Function.h"

using namespace std;

string mathSympols = "+-*/=";

Function *parseStringWithFunctions(string function) {
    int i = 0, r = 0, start = 0;
    while (function[i] != '\0') {
        if (mathSympols.find(function[i])) {
            function.substr(start, i);
            start = i;
            r++;
        }
    }
    return nullptr;
}

int main() {

    double p, p0 = 1, eps = 0.00001;
    int i = 0, N = 10000;

    string function;

    cin >> function;
    parseStringWithFunctions(function);


    return 0;
}
