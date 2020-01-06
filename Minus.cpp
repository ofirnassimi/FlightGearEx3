//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "Minus.h"

Minus::Minus(Expression* pExLeft, Expression* pExRight)
        : BinaryOperator(pExLeft, pExRight)
{

}

Minus::~Minus()
{
}

double Minus::calculate()
{
    return left->calculate() - right->calculate();
}