//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_BINARYOPERATOR_H
#define FLIGHTGEAREX3_BINARYOPERATOR_H

#include <iostream>
#include "Expression.h"

class BinaryOperator: public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryOperator(Expression* pExLeft = nullptr, Expression* pExRight = nullptr){
        left = pExLeft;
        right = pExRight;
    }
    virtual ~BinaryOperator() {
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right=nullptr;
        }
    }

    virtual double calculate()=0;
};

#endif //FLIGHTGEAREX3_BINARYOPERATOR_H
