//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_UNARIOPERATOR_H
#define FLIGHTGEAREX3_UNARIOPERATOR_H

#include <iostream>
#include "Expression.h"

class UnariOperator: public Expression {
protected:
    Expression* m_pEx;
public:
    UnariOperator(Expression* pEx = nullptr);
    virtual ~UnariOperator();
    virtual double calculate() = 0;
};


#endif //FLIGHTGEAREX3_UNARIOPERATOR_H
