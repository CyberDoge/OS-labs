//
// Created by cyberdoge on 12.03.19.
//

#include "Cos.h"
#include <math.h>

double Cos::countValue(double value) {
    return k * cos(value);
}

double Cos::revers(double value) {
    value = value / Function::k;
    return acos(value);
}
