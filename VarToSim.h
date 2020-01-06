//
// Created by inbar on 01/01/2020.
//

#ifndef EX3__VARTOSIM_H_
#define EX3__VARTOSIM_H_

#include <unordered_map>
//#include "Variable.h"
#include "ex1.h"

using namespace std;

class VarToSim {
 private:
  unordered_map<string, Variable*> myMap;
  static VarToSim *s;

  VarToSim() {

  }

 public:
  unordered_map<string, Variable*> getInstance() {
    return myMap;
  }
  void add(string name, string address, float value) {
    Variable *v = new Variable(address, value);
    this->myMap[name] = v;
  }
  void updateVar(string name, float num) {
    Variable *v = new Variable(this->myMap.at(name)->getName(), num);
    this->myMap.at(name) = v;
  }
  static VarToSim *instance() {
    if(!s) {
      s = new VarToSim();
    }
    return s;
  }
};


#endif //EX3__VARTOSIM_H_