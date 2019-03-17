//
// Created by cyberdoge on 13.03.19.
//

#include "Exp.h"
#include <math.h>

double Exp::countValue(double value) {
    return k*exp(value);
}

double Exp::revers(double value) {
    value /= Function::k;
    return log(value);
}
