//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "Div.h"

Div::Div(Expression* pExLeft, Expression* pExRight) : BinaryOperator(pExLeft, pExRight)
{
}

Div::~Div()
{
}

double Div::calculate()
{
    if (right->calculate() < 1e-100) {
        throw "division by zero";
    }
    return (left->calculate() / right->calculate());
}