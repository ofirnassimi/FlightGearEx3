//
// Created by ofir on 03/01/2020.
//

#include <iostream>
#include <stdexcept>
#include "ex1.h"
#include "Interpreter.h"

Interpreter::Interpreter() {
    m_Vars.clear();

}

Interpreter::~Interpreter() {
    Variable* v = nullptr;
    while(!m_Vars.empty()) {
        std::map<std::string, Variable*>::iterator it = m_Vars.begin();
        v = (*it).second;
        delete v;
        m_Vars.erase(it);
    }
}

void Interpreter::setVariables(std::string strVars)
{
    size_t indexVarBegin = 0;
    size_t indexEQ = 0;
    size_t indexColon  = 0;
    bool bEndReached = false;

    while ( !bEndReached) {
        indexEQ = strVars.find('=', indexVarBegin);
        if(indexEQ == std::string::npos) {
            if(indexColon == 0) {
                // indicates the first search
                throw "illegal variable assignment!";
            } else {
                bEndReached = true;
            }
        } else {
            // '=' was found
            indexColon = strVars.find(';', indexEQ+1);
            if (indexColon == std::string::npos) {
                // no more ';'. This is the last expression
                bEndReached = true;
                indexColon = strVars.length();
            }
            std::string strVarDef = strVars.substr(indexVarBegin, indexEQ- indexVarBegin);
            std::string strVarVal = strVars.substr(indexEQ+1, (indexColon-1)-indexEQ);
            indexVarBegin = indexColon+1;

            if (Variable::ValidateVarName(strVarDef)) {
            //if (Variable::ValidateVarName(strVarDef) && Value::ValidateValue(strVarVal)) {
                Variable* v = new Variable(strVarDef, std::stod(strVarVal));
                std::pair<std::string, Variable*> mapEntry(strVarDef, v);
                std::map<std::string, Variable*>::iterator iter = m_Vars.find(strVarDef);
                if(iter != m_Vars.end()) {
                    //variable exists
                    delete (*iter).second;
                    m_Vars.erase(iter);
                }
                m_Vars.insert(mapEntry);
            } else {
                throw "illegal variable assignment!";
            }
        }
    }
}

void Interpreter::_handleNumber(std::string& strIn, size_t& index)
{
    size_t iNumBegin = index;
    try {
        std::string substr = strIn.substr(iNumBegin, strIn.length() - iNumBegin);
        std::stod(substr,&index);
        index += iNumBegin;
    } catch (const std::invalid_argument& ia) {
        throw "Invalid argument";
    }
    std::string tmp = strIn.substr(iNumBegin, index - iNumBegin);
    m_outputQ.push(tmp);
}

bool Interpreter::_readVariable(std::string& strIn,size_t& index)
{
    bool bRet = true;
    size_t iStartOfVarName = index;
    bool bCont = true;
    while (bCont && strIn.length() > index) {
        char c = strIn.at(index);
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c>='0' && c<='9') ) {
            ++index;
        } else {
            //character is NOT a valid variable alphabet -> we finished reading the name
            bCont = false;
            if (c == '+' || c == '-' || c== '*' || c== '/' || c== ')') {
                // these are the only tokens that can follow a variable name
                //construct the variable name
                std::string strVarName = strIn.substr(iStartOfVarName, index-iStartOfVarName);
                //verify that the variable is defined
                if (m_Vars.find(strVarName) != m_Vars.end()) {
                    // put variable in queue
                    m_outputQ.push(strVarName);
                }
            } else {
                bRet = false;
            }
        }
    }
    return bRet;
}

void Interpreter::_Shunting_Yard(std::string strIn)
{
    bool bReadOperator = false;
    for (size_t index = 0; index < strIn.length();) {
        char tok = strIn.at(index);
        switch (tok) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                _handleNumber(strIn, index);
                bReadOperator = false;
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                if(bReadOperator){
                    throw "illegal math expression";
                } else {
                    bReadOperator = true;
                }
                if (strIn.at(++index) == '(') {
                    if (tok == '-') {
                        // special treatment for negation operator
                        // for our purposes, '#' replaces '-'
                        tok = '#';
                    }
                    if (tok == '+') {
                        tok = '$';
                    }
                }
                _handleOperator(tok);
                break;
            case '(':
                bReadOperator = false;
                m_OperStck.push(tok);
                ++index;
                break;
            case ')':
                bReadOperator = false;
                _handleRightP();
                ++index;
                break;
            default:
                bReadOperator = false;
                _readVariable(strIn,index);
                break;
        }
    }
    while (!m_OperStck.empty()) {
        _MoveStackToQueue();
    }
}

void Interpreter::_MoveStackToQueue()
{
    std::string str(1, m_OperStck.top());
    m_outputQ.push(str);
    m_OperStck.pop();

}

void Interpreter::_handleRightP()
{
    while (!m_OperStck.empty() && m_OperStck.top() != '(') {
        _MoveStackToQueue();
    }
    if (m_OperStck.empty()) {
        throw "mismatched parantheses";
    } else {
        m_OperStck.pop();
    }
}

unsigned char Interpreter::_getPrecedence(char oper)
{
    unsigned char ucRet = 1;
    switch (oper) {
        case '*':
        case '/':
            ucRet = 3;
            break;
        case '+':
        case '-':
            ucRet = 2;
            break;
        case '(':
            ucRet = 5;
            break;
        default:
            break;
    }
    return ucRet;
}

void Interpreter::_handleOperator(char oper)
{
    while (!m_OperStck.empty() && (_getPrecedence(m_OperStck.top()) >= _getPrecedence(oper)) && m_OperStck.top() != '(') {
        _MoveStackToQueue();
    }
    m_OperStck.push(oper);

}

Expression* Interpreter::interpret(std::string strIn)
{
    _Shunting_Yard(strIn);
    return _processQueue();
}

Expression* Interpreter::_processQueue()
{
    Expression* expr = nullptr;
    std::stack<Expression*> qOperands;
    while (!m_outputQ.empty()) {
        std::string strOperand = m_outputQ.front();
        bool bBinaryOperator = false;
        if (isOperator(strOperand, bBinaryOperator)) {
            Expression* pLeft = nullptr;;
            Expression* pRight = nullptr;
            if (bBinaryOperator) {
                pRight = qOperands.top();
                qOperands.pop();
            }
            if (qOperands.empty()) {
                pLeft = expr;
            } else {
                pLeft = qOperands.top();
                qOperands.pop();
            }
            switch (strOperand.at(0)) {
                case '+':
                    expr = new Plus(pLeft, pRight);
                    break;
                case '-':
                    expr = new Minus(pLeft, pRight);
                    break;
                case '*':
                    expr = new Mul(pLeft, pRight);
                    break;
                case '/':
                    expr = new Div(pLeft, pRight);
                    break;
                case '#':
                    expr = new UMinus(pLeft);
                    break;
                case '$':
                    expr = new UPlus(pLeft);
                    break;
                default:
                    break;
            }
            if (m_outputQ.size() > 1) {
                //there are still operands, we expect more operators
                //output queue still hasn't popped the operator, so its size is at least 1
                qOperands.push(expr);
            }

        } else {
            double dNumber;
            Expression* pOperand = nullptr;
            if (_isNumber(strOperand, &dNumber)) {
                pOperand = new Value(dNumber);
            } else {
                std::map<std::string, Variable*>::iterator it = m_Vars.find(strOperand);
                if (it != m_Vars.end()) {
                    pOperand = new Variable(it->second->getName(), it->second->getValue());
                }
            }
            qOperands.push(pOperand);
        }
        m_outputQ.pop();
    }

    return expr;
}

bool Interpreter::isOperator(std::string strOperand, bool& bBinaryOperator)
{
    bool bRet = false;
    bBinaryOperator = false;
    switch (strOperand.at(0)) {
        case '+':
        case '-':
        case '*':
        case '/':
            bBinaryOperator = true;
            bRet = true;
            break;
        case '#':
        case '$':
            bBinaryOperator = false;
            bRet = true;
            break;
        default:
            break;
    }
    return bRet;
}

bool Interpreter::_isNumber(std::string strOperand, double* d)
{
    bool bRet = true;
    try {
        *d = std::stod(strOperand, nullptr);
    } catch (const std::invalid_argument& ia) {
        bRet = false;
    }
    return bRet;
}

