//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_INTERPRETER_H
#define FLIGHTGEAREX3_INTERPRETER_H

#include <string>
#include <queue>
#include <stack>
#include <map>

class Variable;
class Expression;
class Interpreter {
    enum Tokens{
        eMINUS = '-',
        ePLUS = '+',
        eMUL = '*',
        eDIV = '/',
        eLPAR = '(',
        eRPAR = ')'
    };

    std::queue<std::string> m_outputQ;
    std::stack<char> m_OperStck;
    std::map<std::string, Variable*> m_Vars;

    bool _isNumber(std::string strOperand, double* d);
    bool isOperator(std::string strOperand, bool& bBinaryOperator);
    Expression* _processQueue();
    void _Shunting_Yard(std::string strIn);
    void _handleOperator(char oper);
    unsigned char _getPrecedence(char oper);
    void _handleRightP();
    void _handleNumber(std::string& strIn, size_t& index);
    bool _readVariable(std::string& strIn,size_t& index);
    void _MoveStackToQueue();
public:
    Interpreter();
    virtual ~Interpreter();

    Expression* interpret(std::string strIn);
    void setVariables(std::string strVars);

};

#endif //FLIGHTGEAREX3_INTERPRETER_H
