//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_UPLUS_H
#define FLIGHTGEAREX3_UPLUS_H

#include "UnariOperator.h"

class UPlus: public UnariOperator {
public:
    UPlus(Expression* pEx);
    virtual ~UPlus();
    virtual double calculate();
};

#endif //FLIGHTGEAREX3_UPLUS_H
