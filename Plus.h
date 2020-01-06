//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_PLUS_H
#define FLIGHTGEAREX3_PLUS_H

#include <iostream>
#include "BinaryOperator.h"

class Plus : public BinaryOperator {
public:
    Plus(Expression* pExLeft = nullptr, Expression* pExRight = nullptr);
    virtual ~Plus();
    virtual double calculate();
};

#endif //FLIGHTGEAREX3_PLUS_H
