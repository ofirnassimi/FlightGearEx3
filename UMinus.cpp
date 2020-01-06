//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "UMinus.h"

UMinus::UMinus(Expression* pEx) : UnariOperator(pEx) {
}

UMinus::~UMinus() {
}

double UMinus::calculate() {
    return -(m_pEx->calculate());
}