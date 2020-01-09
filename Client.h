//
// Created by ofir on 25/12/2019.
//

#include <sys/socket.h>
#include <iostream>
#include <rpc/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
#include <thread>
#include <pthread.h>
#include <sstream>
#include "toClient.h"
#include "Singleton.h"
#include <mutex>

using namespace std;
toClient *toClient::s;

struct Client {
    string IP;
    int port;

    Client(string str, int p) {
        this->IP = str;
        this->port = p;
    }


    int openClient() {

        //create socket
        int client_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket == -1) {
            cerr << "Could not create a socket" << endl;
            return -1;
        }

        //socket address
        sockaddr_in address;
        address.sin_family = AF_INET;

        //delete the " at the beginning and the end of the IP string
        string newIP = IP;
        newIP.erase(0,1);
        newIP.erase(newIP.size() - 1, 1);

        address.sin_addr.s_addr = inet_addr(newIP.c_str());
        address.sin_port = htons(this->port);

        //request a connection with the server
        int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
        if (is_connect == -1) {
            cerr << "Could not connect to server" << endl;
            return -2;
        } else {
            cout << "Client is now connected to server" << endl;
        }

        thread thread_object(clientThread, client_socket);
        thread_object.detach();

        return 0;
    }


    /**
     * Takes values from singleton map and sends them to the server (simulator)
     * @param client_socket
     */
    static void clientThread(int client_socket) {
        int is_sent;
        vector<string> arr = Singleton::buildArray();
        //while(!IsDone::instance()->getInstance()) {
        while(true) {
            for(int i = 0; i < arr.size(); i++) {
                stringstream ss;
                ss << "set " << arr[i] << " " << toClient::instance()->getInstance().at(arr[i]) << "\r\n";
                string s = ss.str();
                char const *message = s.c_str();
                is_sent = send(client_socket, message, strlen(message), 0);
                if (is_sent == -1) {
                    cout << "Error sending message" << endl;
                }
            }
            sleep(2);
        }
        //close(client_socket);
    }
};

