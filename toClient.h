//
// Created by ofir on 03/01/2020.
//

#ifndef EX3__TOCLIENT_H_
#define EX3__TOCLIENT_H_

#include <unordered_map>
#include <vector>
#include "Singleton.h"
#include "VarToSim.h"

using namespace std;

class toClient {
private:
    unordered_map<string, float> myMap;
    static toClient *s;

    toClient() {

    }

public:
        unordered_map<string, float> getInstance() {
        vector<string> arr = Singleton::instance()->buildArray();
        unordered_map <string, float> newMap;
        for (auto it : VarToSim::instance()->getInstance()) {
            newMap[it.second->getName()] = it.second->getValue();
        }
        for(int i = 0; i < arr.size(); i++) {
            if (newMap.find(arr[i]) == newMap.end()) {
                Singleton::mutex_lock.lock();
                newMap[arr[i]] = Singleton::instance()->getInstance().at(arr[i]);
                Singleton::mutex_lock.unlock();
            }
        }
        myMap = newMap;
        return myMap;
    }
    static toClient *instance() {
        if(!s) {
            s = new toClient;
        }
        return s;
    }
};

#endif //EX3__TOCLIENT_H_