//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_DIV_H
#define FLIGHTGEAREX3_DIV_H

#include "BinaryOperator.h"

class Div: public BinaryOperator {
public:
    Div(Expression* pExLeft = nullptr, Expression* pExRight = nullptr);
    virtual ~Div();
    double calculate();
};

#endif //FLIGHTGEAREX3_DIV_H