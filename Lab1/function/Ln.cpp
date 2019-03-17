//
// Created by cyberdoge on 14.03.19.
//

#include "Ln.h"
#include <math.h>

double Ln::countValue(double value) {
    return k*log(value);
}

double Ln::revers(double value) {
    value /= Function::k;
    return exp(value);
}
