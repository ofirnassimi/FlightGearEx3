//
// Created by inbar on 03/01/2020.
//

#ifndef EX3__GLOBFUNCTIONS_H_
#define EX3__GLOBFUNCTIONS_H_
#include <string>
#include "VarToSim.h"
#include "ConstVars.h"
#include "Vars.h"
#include "ex1.h"
#include <iostream>
using namespace std;

string isVar(string var);

void updateVar(string varType, string var, float value);

float solveExpression(string expression);

#endif //EX3__GLOBFUNCTIONS_H_