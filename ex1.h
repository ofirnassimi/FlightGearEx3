//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_EX1_H
#define FLIGHTGEAREX3_EX1_H

#include "Value.h"
#include "UMinus.h"
#include "UPlus.h"
#include "Plus.h"
#include "Minus.h"
#include "Mul.h"
#include "Div.h"
#include "Variable.h"
#include "Interpreter.h"

using namespace std;

#endif //FLIGHTGEAREX3_EX1_H



//
// Created by liel and adi on 1/1/20.
//

//#ifndef FLYSIMULATOR1_0_EX1_H
//#define FLYSIMULATOR1_0_EX1_H
//
//#include "Expression.h"
//#include <string>
//#include <iostream>
//#include <map>
//#include <set>
//#include <stack>
//#include <queue>
////#include "Singleton.h"
//#include <map>
//using namespace std;
//
//class Value : public Expression {
//protected:
//    float val;
//public:
//    Value(float val);
//    float calculate();
//};
//
//class Variable: public Expression {
//protected:
//    double num;
//    string str;
//public:
//    Variable &operator++();
//    Variable &operator++(int);
//    Variable &operator--();
//    Variable &operator--(int);
//    Variable(string str, float num);
//    double calculate();
//    void setValue(float value);
//    double getValue();
//    string getName();
//};
//
//class BinaryOperator : public Expression {
//protected:
//    Expression *left;
//    Expression *right;
//public:
//    BinaryOperator(Expression* left, Expression* right);
//    ~BinaryOperator() {
//        delete left;
//        delete right;
//    }
//};
//class UnaryOperator : public Expression {
//protected:
//    Expression* expression;
//public:
//    UnaryOperator(Expression* expression);
//    ~UnaryOperator() {
//        delete expression;
//    }
//};
//class UMinus : public UnaryOperator {
//    Expression* expression;
//public:
//    UMinus(Expression* expression);
//    double calculate();
//};
//class UPlus : public UnaryOperator {
//    Expression* expression;
//public:
//    UPlus(Expression* expression);
//    double calculate();
//};
//class Plus : public BinaryOperator {
//    Expression *left;
//    Expression *right;
//public:
//    Plus(Expression *left, Expression *right);
//
//    double calculate();
//};
//class Mul : public BinaryOperator {
//    Expression *left;
//    Expression *right;
//public:
//    Mul(Expression *left, Expression *right);
//
//    double calculate();
//};
//class Div : public BinaryOperator {
//    Expression *left;
//    Expression *right;
//public:
//    Div(Expression *left, Expression *right);
//
//    double calculate();
//};
//class Minus : public BinaryOperator {
//    Expression *left;
//    Expression *right;
//public:
//    Minus(Expression *left, Expression *right);
//    double calculate();
//};
//
//
//
//class Interpreter {
//public:
//    map <string, double > mapA;
//    void setVariables(string str);
//    Expression* interpret(string str);
//    string checkSpace(string str);
//    void enterMap();
//};
//
//#endif //FLYSIMULATOR1_0_EX1_H