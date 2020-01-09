//
// Created by inbar on 03/01/2020.
//

#include <sstream>
#include "globFunctions.h"

/**
 * checks if the string is kind of variable and if it is, it returns what kind of variable
 */
string isVar(string var) {
    if (VarToSim::instance()->getInstance().find(var) != VarToSim::instance()->getInstance().end()) {
        return "VarToSim";
    } else if (ConstVars::instance()->getInstance().find(var) != ConstVars::instance()->getInstance().end()) {
        return "ConstVars";
    } else if (Vars::instance()->getInstance().find(var) != Vars::instance()->getInstance().end()) {
        return "Vars";
    } else {
        return "no";
    }
}

void updateVar(string varType, string var, float value) {
    if (varType == "VarToSim") {
        //replace
        VarToSim::instance()->updateVar(var, value);
        // if exists replace, otherwise make new
    } else if (varType == "ConstVars") {
        ConstVars::instance()->updateVar(var, value);
    }
}


bool is_number( string myString ) {
    std::istringstream iss(myString);
    float f;
    iss >> noskipws >> f; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
}

string removeSpaces(string str)
{
    string ret = "";
    for(int i = 0; i < str.length(); i++) {
        if (str[i] != ' ') {
            ret += str[i];
        }
    }
    return ret;
}

/**
 * gets a string and returns the number of it after calculation
 */
float solveExpression(string expression) {
    expression = removeSpaces(expression);
    Interpreter *it = new Interpreter();
    int check = 0;
    // search for variables
    int i;
    string command;
    for (i = 0; i < expression.length(); i++) {
        command = "";
        while ((expression[i] != ',') && (expression[i] != '(') && (expression[i] != ' ') && (expression[i] != ')') &&
               (expression[i] != '\t') && (expression[i] != '+') && (expression[i] != '-') && (expression[i] != '*') &&
               (expression[i] != '/') && (i < expression.length())) {
            command += expression[i];
            i++;
        }
        if (command != "") {
            // if not a number, operator etc. check for variables
            if (!is_number(command)) {
                if (command == expression)
                {
                    check = 1;
                }
                string vType = isVar(command);
                if (vType == "no") {
                    cout << "error: what is " << command << endl;
                } else {
                    std::ostringstream oss;
                    if (vType == "Vars") {
                        oss << command << "=" << Vars::instance()->getByName(command);
                    } else if (vType == "VarToSim") {
                        oss << command << "=" << VarToSim::instance()->getInstance().at(command)->getValue();
                    } else if (vType == "ConstVars") {
                        oss << command << "=" << ConstVars::instance()->getInstance().at(command);
                    }
                    string val = oss.str();
                    it->setVariables(val);
                }
            }
        }
    }
    if ((is_number(expression)) || check) {
        expression += "+0";
    }
    // solve and return answer
    Expression *ans = it->interpret(expression);
    return ans->calculate();
}