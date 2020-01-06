////
//// Created by liel and adi on 1/1/20.
////
//
//
//#include "ex1.h"
//#include "Singleton.h"
//#include "Vars.h"
//#include "ConstVars.h"
//
//using namespace std;
//
//BinaryOperator::BinaryOperator(Expression *left1, Expression *right1) {
//    this->right = right1;
//    this->left = left1;
//}
//Value::Value(float val1){
//    this->val = val1;
//}
//UnaryOperator::UnaryOperator(Expression* expression1) {
//    this->expression = expression1;
//}
//UMinus::UMinus(Expression *expression1):UnaryOperator(expression1) {
//    this->expression = expression1;
//}
//double UMinus :: calculate(){
//    return -1 * (this->expression->calculate());
//}
//UPlus::UPlus(Expression *expression1):UnaryOperator(expression1) {
//    this->expression = expression1;
//}
//double UPlus :: calculate(){
//    return (this->expression->calculate());
//}
//
//double Value :: calculate() {
//    return this->val;
//}
//Mul::Mul(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
//    this->left = left1;
//    this->right = right1;
//}
//double Mul :: calculate() {
//    return (this->right->calculate() * this->left->calculate());
//}
//Div::Div(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
//    this->left = left1;
//    this->right = right1;
//}
//double Div :: calculate() {
//    if (right->calculate() == 0) {
//        throw ("division by zero");
//    }
//    return (this->left->calculate() / this->right->calculate());
//}
//Minus::Minus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
//    this->left = left1;
//    this->right = right1;
//}
//double Minus :: calculate() {
//    return (this->left->calculate() - this->right->calculate());
//}
//Plus::Plus(Expression *left1, Expression *right1) : BinaryOperator(left1, right1) {
//    this->left = left1;
//    this->right = right1;
//}
//double Plus :: calculate() {
//    return (this->right->calculate() + this->left->calculate());
//}
//Variable::Variable(string str1, float num1) {
//    this->num = num1;
//    this->str = str1;
//}
//void Variable::setValue(float value) {
//    this->num = value;
//}
//double Variable::getValue() {
//    return this->num;
//}
//string Variable::getName()  {
//    return this->str;
//}
//double Variable :: calculate() {
//    return this->num;
//}
//Variable& Variable:: operator++() {
//    num++;
//    return *this;
//}
//Variable&  Variable::operator++(int) {
//    num++;
//    return *this;
//}
//Variable& Variable:: operator--() {
//    num--;
//    return *this;
//}
//Variable&  Variable::operator--(int) {
//    // Variable temp = *this;
//    num--;
//    return *this;
//}
//void Interpreter::enterMap() {
//    //Singleton *singleton = singleton->getInstance();
//    for (auto element : Vars::instance()->getInstance()) {
//    //for (auto element : singleton->infoFromSimulator) {
//        mapA[element.first] = element.second.
//    }
//    for (auto element : ConstVars::instance()->getInstance()) {
//    //for (auto element : singleton->singerVar) {
//        mapA[element.first] = element.second.getValue();
//    }
//}
//
//Expression *Interpreter::interpret(string str) {
//    set<char> operatorsChar = {'*', '/', '+', '-', '(', ')'};
//    set<string> operatorsString = {"*", "/", "+", "-", "(", ")", "@", "#"};
//    stack<string> stack;
//    queue<string> queue;
//    unsigned int i;
//    str = checkSpace(str);
//    if(mapA.find(str) != mapA.end()) {
//        Expression *expression = new Value(mapA.find(str)->second);
//        return expression;
//    }
//    for (i = 0; i < str.length(); i++) {
//        if (((str[i] == '+') || (str[i] == '-')) && ((i == 0) || str[i - 1] == '(')) {
//            while ((!stack.empty()) && ((stack.top() == "@") || (stack.top() == "#"))) {
//                queue.push(stack.top());
//                stack.pop();
//            }
//            if (str[i] == '-') {
//                stack.push("@");
//            } else if (str[i] == '+') {
//                stack.push(("#"));
//            }
//        } else if ((str[i] == '*') || (str[i] == '/')) {
//            while ((!stack.empty()) &&
//                   ((stack.top() == "/") || (stack.top() == "@") || (stack.top() == "*") || (stack.top() == "#"))) {
//                queue.push(stack.top());
//                stack.pop();
//            }
//            stack.push(string(1, str[i]));
//        } else if ((str[i] == '+') || (str[i] == '-')) {
//            while ((!stack.empty()) &&
//                   ((stack.top() == "/") || (stack.top() == "@") || (stack.top() == "*") || (stack.top() == "-") ||
//                    (stack.top() == "+") || (stack.top() == "#"))) {
//                queue.push(stack.top());
//                stack.pop();
//            }
//            stack.push(string(1, str[i]));
//        } else if (str[i] == '(') {
//            stack.push("(");
//        } else if (str[i] == ')') {
//            while ((!stack.empty()) && (stack.top() != "(")) {
//                queue.push(stack.top());
//                stack.pop();
//            }
//            if (stack.empty()) {
//                throw ("no mach paren");
//            }
//            stack.pop();
//        } // else its number or variabel
//
//        else {
//            int j = i + 1;
//            while (operatorsChar.find(str[j]) == operatorsChar.end()) {
//                j++;
//            }
//            string sub = str.substr(i, j - i);
//            queue.push(sub);
//            i = j - 1;
//        }
//    }
//    while (!stack.empty()) {
//        if (stack.top() == "(") {
//            throw ("no mach paren");
//        }
//        queue.push(stack.top());
//        stack.pop();
//    }
//    ::stack<Expression *> newStack;
//    while (!queue.empty()) {
//        if (!newStack.empty()) {
//        }
//        string x = queue.front();
//        Expression *left;
//        Expression *right;
//        queue.pop();
//        if (operatorsString.find(x) == operatorsString.end()) { // not op
//            if (this->mapA.find(x) != mapA.end()) { // in map
//                newStack.push(new Variable(x, mapA[(x)]));
//            } else {
//                try {
//                    double d = stod(x);
//                    newStack.push((new Value(d)));
//                } catch (...) {
//                    throw ("illegal math expression");
//                }
//            }
//        } else {
//            if (x == "@" || x == "#") {
//                if (newStack.size() < 1) {
//                    throw ("illegal variable assignment!");
//                }
//            } else {
//                if (newStack.size() < 2) {
//                    throw ("illegal variable assignment!");
//                }
//            }
//            if (x == "@") {
//                left = newStack.top();
//                newStack.pop();
//                newStack.push(new UMinus(left));
//            } else if (x == "#") {
//                left = newStack.top();
//                newStack.pop();
//                newStack.push(new UPlus(left));
//            } else if (x == "+") {
//                right = newStack.top();
//                newStack.pop();
//                left = newStack.top();
//                newStack.pop();
//                newStack.push(new Plus(left, right));
//            } else if (x == "-") {
//                right = newStack.top();
//                newStack.pop();
//                left = newStack.top();
//                newStack.pop();
//                newStack.push(new Minus(left, right));
//            } else if (x == "*") {
//                right = newStack.top();
//                newStack.pop();
//                left = newStack.top();
//                newStack.pop();
//                newStack.push(new Mul(left, right));
//            } else if (x == "+") {
//                right = newStack.top();
//                newStack.pop();
//                left = newStack.top();
//                newStack.pop();
//                newStack.push(new Plus(left, right));
//            } else if (x == "/") {
//                right = newStack.top();
//                newStack.pop();
//                left = newStack.top();
//                newStack.pop();
//
//                newStack.push(new Div(left, right));
//            }
//
//        }
//    }
//    if (newStack.size() != 1) {
//        throw ("error");
//    }
//    return newStack.top();
//}
//string Interpreter :: checkSpace(string str) {
//    unsigned i;
//    string final = "";
//    for(i = 0; i < str.size() ; i++) {
//        if (str[i] != ' ') {
//            final = final + str[i];
//        }
//    }
//    return final;
//}