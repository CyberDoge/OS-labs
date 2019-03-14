//
// Created by cyberdoge on 12.03.19.
//

#ifndef LAB1_FUNCTION_H
#define LAB1_FUNCTION_H

class Function
{
protected:
    double k = 1;
    double arg = 1;

  public:
    virtual double countValue(double value) = 0;

    virtual double setK(double value)
    {
        k = value;
    };

    virtual double setArg(double value)
    {
        arg = value;
    };

    virtual double revers(double value) = 0;
};

#endif //LAB1_FUNCTION_H
