//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "UPlus.h"

UPlus::UPlus(Expression* pEx) : UnariOperator(pEx) {
}

UPlus::~UPlus() {
}

double UPlus::calculate() {
    return m_pEx->calculate();
}
