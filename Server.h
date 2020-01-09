#include <sys/socket.h>
#include <iostream>
#include <rpc/types.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <pthread.h>
#include <unordered_map>
#include "Singleton.h"
#include <vector>
#include <mutex>
#include <sstream>

using namespace std;
Singleton *Singleton::s;

struct  Server {
    int port;

    Server(int p) {
        this -> port = p;
    }

    /**
     * reads the buffer (a line with values we get from the simulator) and adds them to a map by their path and by their
     * place in the buffer
     */
    static void buffToMap(char buffer[]) {
        unordered_map<string, float> ret;
        vector<string> names = Singleton::instance()->buildArray();
        int i = 0;
        int place = 0;
        string word;
        while ((place < 1024) && (((buffer[place] >= '0') && (buffer[place] <= '9')) || (buffer[place] == ',') ||
                                  (buffer[place] == '.') || (buffer[place] == '-'))) { //while place < buffer.length
            if (buffer[place] == ',') {
                ret[names[i]] = stof(word);
                i++;
                word ="";
            } else {
                word += buffer[place];
            }
            place++;
        }
        ret[names[i]] = stof(word);
        Singleton::mutex_lock.lock();
        Singleton::instance()->setInstance(ret);
        Singleton::mutex_lock.unlock();
    }

    void openServer() {

        //create socket
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd == -1) {
            cerr << "Could not create a socket" << endl;
        }


        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(this->port);

        if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
            cerr << "Could not bind the socket to an IP" << endl;
        }


        //making socket listen to the port
        if (listen(socketfd, 5) == -1) {
            cerr << "Error during listening command" << endl;
        }


        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
        if (client_socket == -1) {
            cerr << "Error accepting client" << endl;
        }

        char buffer[1024] = {0};
        int valread = read(client_socket, buffer, 1024);
        buffToMap(buffer);

        thread thread_obj(readFromClient, client_socket);
        thread_obj.detach();
    }

    /**
     * a function we send to the thread - reads from the simulator
     * @param client_socket
     */
    static void readFromClient(int client_socket) {
        //while(!IsDone::instance()->getInstance()) {
        while(true) {
            char buffer[1024] = {0};
            int valread = read(client_socket, buffer, 1024);
            buffToMap(buffer);
        }
        //close(client_socket);
    }
};
