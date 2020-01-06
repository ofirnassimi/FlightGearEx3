//
// Created by ofir on 03/01/2020.
//

#ifndef FLIGHTGEAREX3_EXPRESSION_H
#define FLIGHTGEAREX3_EXPRESSION_H

/**
 * Expression Interface
 */
class Expression {
protected:
public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //FLIGHTGEAREX3_EXPRESSION_H
