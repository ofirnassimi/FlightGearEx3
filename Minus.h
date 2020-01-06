//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_MINUS_H
#define FLIGHTGEAREX3_MINUS_H

#include <iostream>
#include "BinaryOperator.h"

class Minus: public BinaryOperator {
public:
    Minus(Expression* pExLeft = nullptr, Expression* pExRight = nullptr);
    virtual ~Minus();
    virtual double calculate();
};

#endif //FLIGHTGEAREX3_MINUS_H
