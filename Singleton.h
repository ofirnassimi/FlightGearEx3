//
// Created by ofir on 28/12/2019.
//

#ifndef EX3_SINGLETON_H
#define EX3_SINGLETON_H

#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>

using namespace std;

/**
 * This singleton map includes all of the values we get straight from the server (by buffer)
 */
class Singleton {

private:
    unordered_map<string, float> myMap;
    static Singleton *s;

    Singleton() {
    }

public:

    /**
     * creates a vector with all of the paths "addresses" from the simulator (from XML file)
     */
    static vector<string> buildArray() {
        vector<string> strVec(36);
        strVec[0] = "/instrumentation/airspeed-indicator/indicated-speed-kt";
        strVec[1] = "/sim/time/warp";
        strVec[2] = "/controls/switches/magnetos";
        strVec[3] = "/instrumentation/heading-indicator/offset-deg";
        strVec[4] = "/instrumentation/altimeter/indicated-altitude-ft";
        strVec[5] = "/instrumentation/altimeter/pressure-alt-ft";
        strVec[6] = "/instrumentation/attitude-indicator/indicated-pitch-deg";
        strVec[7] = "/instrumentation/attitude-indicator/indicated-roll-deg";
        strVec[8] = "/instrumentation/attitude-indicator/internal-pitch-deg";
        strVec[9] = "/instrumentation/attitude-indicator/internal-roll-deg";
        strVec[10] = "/instrumentation/encoder/indicated-altitude-ft";
        strVec[11] = "/instrumentation/encoder/pressure-alt-ft";
        strVec[12] = "/instrumentation/gps/indicated-altitude-ft";
        strVec[13] = "/instrumentation/gps/indicated-ground-speed-kt";
        strVec[14] = "/instrumentation/gps/indicated-vertical-speed";
        strVec[15] = "/instrumentation/heading-indicator/indicated-heading-deg";
        strVec[16] = "/instrumentation/magnetic-compass/indicated-heading-deg";
        strVec[17] = "/instrumentation/slip-skid-ball/indicated-slip-skid";
        strVec[18] = "/instrumentation/turn-indicator/indicated-turn-rate";
        strVec[19] = "/instrumentation/vertical-speed-indicator/indicated-speed-fpm";
        strVec[20] = "/controls/flight/aileron";
        strVec[21] = "/controls/flight/elevator";
        strVec[22] = "/controls/flight/rudder";
        strVec[23] = "/controls/flight/flaps";
        strVec[24] = "/controls/engines/engine/throttle";
        strVec[25] = "/controls/engines/current-engine/throttle";
        strVec[26] = "/controls/switches/master-avionics";
        strVec[27] = "/controls/switches/starter";
        strVec[28] = "/engines/active-engine/auto-start";
        strVec[29] = "/controls/flight/speedbrake";
        strVec[30] = "/sim/model/c172p/brake-parking";
        strVec[31] = "/controls/engines/engine/primer";
        strVec[32] = "/controls/engines/current-engine/mixture";
        strVec[33] = "/controls/switches/master-bat";
        strVec[34] = "/controls/switches/master-alt";
        strVec[35] = "/engines/engine/rpm";

        return strVec;
    }

    unordered_map<string, float> getInstance() {
        return myMap;
    }

    /**
     * changes the exsisting map with a new map
     */
    void setInstance(unordered_map<string, float> newMap) {
        if (myMap.empty()) {
            myMap = newMap;
        }
        vector<string> arr = buildArray();
        for(int i = 0; i < arr.size(); i++) {
            myMap.at(arr[i]) = newMap.at(arr[i]);
        }
    }

    static Singleton *instance() {
        if(!s) {
            s = new Singleton;
        }
        return s;
    }

    static std::mutex mutex_lock;
};


#endif //EX3_SINGLETON_H