//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_MUL_H
#define FLIGHTGEAREX3_MUL_H

#include <iostream>
#include "Mul.h"
#include "BinaryOperator.h"

class Mul: public BinaryOperator {
public:
    Mul(Expression* pExLeft = nullptr, Expression* pExRight = nullptr);
    virtual ~Mul();
    virtual double calculate();
};

#endif //FLIGHTGEAREX3_MUL_H
