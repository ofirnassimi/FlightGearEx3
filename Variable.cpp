//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "Variable.h"

bool Variable::ValidateVarName(std::string& strVarName) {
    bool bRet = true;
    if (!isalpha(strVarName.at(0))) {
        bRet = false;
    }
    for (size_t index = 1; bRet && index < strVarName.length(); ++index) {
        if (!(isalnum(strVarName.at(index)) || strVarName.at(index) == '_')) {
            bRet = false;
        }
    }
    return bRet;
}

Variable::Variable(std::string strName, double dblValue) {
    name = strName;
    value = dblValue;
}

Variable::~Variable() {
}

Variable& Variable::operator ++() {
    value = value + 1;
    return *this;
}

Variable& Variable::operator --() {
    value = value - 1;
    return *this;
}

Variable& Variable::operator +=(double dblValue) {
    value = value + dblValue;
    return *this;
}

Variable& Variable::operator -=(double dblValue) {
    value = value - dblValue;
    return *this;
}

Variable& Variable::operator ++(int intValue) {
    value = value + 1;
    return *this;
}

Variable& Variable::operator --(int intValue) {
    value = value - 1;
    return *this;
}

double Variable::calculate() {
    return value;
}