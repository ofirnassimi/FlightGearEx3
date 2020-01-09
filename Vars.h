#ifndef EX3_VARS_H
#define EX3_VARS_H

#include <unordered_map>
#include <ostream>
#include <iostream>
#include "Singleton.h"

using namespace std;

/**
 * this map includes all of the variables that defined by "<-"
 */
class Vars {
 private:
  unordered_map<string, string> myMap;
  static Vars *s;

  Vars() {

  }

 public:
  unordered_map<string, string> getInstance() {
    return myMap;
  }
  void add(string name, string address) {
    this->myMap[name] = address;
  }
  void setVar(string name, string address) {
    this->myMap.erase(name);
    this->myMap[name] = address;
  }
  float getByName(string name) {
      Singleton::mutex_lock.lock();
      float ret = Singleton::instance()->getInstance().at(myMap.at(name));
      Singleton::mutex_lock.unlock();
      return ret;
  }
    float getByAddress(string address) {
        Singleton::mutex_lock.lock();
        float ret = Singleton::instance()->getInstance().at(address);
        Singleton::mutex_lock.unlock();
        return ret;
  }
  static Vars *instance() {
    if(!s) {
      s = new Vars;
    }
    return s;
  }
};


#endif //EX3_SINGLETON_H