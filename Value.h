//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_VALUE_H
#define FLIGHTGEAREX3_VALUE_H

#include <iostream>
#include "Expression.h"

class Value: public Expression {
private:
    double* m_value;
public:
    Value(double v);
    virtual ~Value();
    virtual double calculate();
    static bool ValidateValue(std::string& strValue);
};
#endif //FLIGHTGEAREX3_VALUE_H
