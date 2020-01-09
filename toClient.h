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

/**
 * this is the map that we send to the simulator (when we are the client)
 */
class toClient {
private:
    unordered_map<string, float> myMap;
    static toClient *s;

    toClient() {

    }

public:
        /**
        * goes through the map that has the variables that defined by "->" and adds them to this map and for the rest
         * of the variables it takes from the singleton map (that has values straight from the buffer)
        */
        unordered_map<string, float> getInstance() {

            vector<string> arr = Singleton::instance()->buildArray();
            unordered_map<string, float> newMap;

            //first put in the toClient map all of the variables from the VarToSim map
            for (auto it : VarToSim::instance()->getInstance()) {
                newMap[it.second->getName()] = it.second->getValue();
            }

            //now check which variables are not yet in the toClient map, and add them to the map by the singleton map
            for (int i = 0; i < arr.size(); i++) {
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
        if (!s) {
            s = new toClient;
        }
        return s;
    }

    //static std::mutex mutex_lock;
};

#endif //EX3__TOCLIENT_H_