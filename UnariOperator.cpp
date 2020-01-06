//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "UnariOperator.h"

UnariOperator::UnariOperator(Expression* pEx) {
    m_pEx = pEx;
}

UnariOperator::~UnariOperator() {
    if (m_pEx) {
        delete m_pEx;
    }
}