//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "Mul.h"

Mul::Mul(Expression* pExLeft, Expression* pExRight)	: BinaryOperator(pExLeft, pExRight) {
}

Mul::~Mul() {
}

double Mul::calculate() {
    return left->calculate() * right->calculate();
}