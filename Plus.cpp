//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "Plus.h"

Plus::Plus(Expression* pExLeft, Expression* pExRight) 	: BinaryOperator(pExLeft, pExRight) {
}

Plus::~Plus() {
};

double Plus::calculate() {
    return left->calculate() + right->calculate();
}