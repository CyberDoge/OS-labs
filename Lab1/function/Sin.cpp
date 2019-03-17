//
// Created by cyberdoge on 12.03.19.
//

#include "Sin.h"
#include <math.h>
double Sin::countValue(double value) {
    return k*sin(value);
}

double Sin::revers(double value) {
    value /= Function::k;
    return asin(value);
}
