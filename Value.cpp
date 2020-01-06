//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include "Value.h"

bool Value::ValidateValue(std::string& strValue) {
    bool bRet = true;
    bool bDecPointPresent = false;
    //can be only decimal digits and at most one '.'
    for (size_t index = 0; bRet && index < strValue.length(); ++index) {
        char c = strValue.at(index);
        if (!isdigit(c)) {
            if (c == '.') {
                if (bDecPointPresent) {
                    bRet = false;
                } else
                    bDecPointPresent = true;
            } else
                bRet = false;
        }
    }
    return bRet;
}

Value::Value(double v) {
    m_value = new double(v);
}

Value::~Value() {
    // TODO Auto-generated destructor stub
    if(m_value) {
        delete m_value;
        m_value = nullptr;
    }
}

double Value::calculate() {
    return (*m_value);
}