//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_UMINUS_H
#define FLIGHTGEAREX3_UMINUS_H

#include "iostream"
#include "UnariOperator.h"

class UMinus: public UnariOperator {
public:
    UMinus(Expression* pEx = nullptr);
    virtual ~UMinus();
    virtual double calculate();
};

#endif //FLIGHTGEAREX3_UMINUS_H
