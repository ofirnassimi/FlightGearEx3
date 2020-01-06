#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "Server.h"
#include "Client.h"
//#include "Vars.h"
//#include "ConstVars.h"
//#include "VarToSim.h"
#include "Variable.h"
#include "globFunctions.h"

using namespace std;

Vars *Vars::s;
ConstVars *ConstVars::s;
VarToSim *VarToSim::s;

class Command {
public:
    virtual int execute(vector<string> commands, int index) = 0;
};


class OpenServerCommand : public Command {

public:
    int execute(vector<string> commands, int index) {

        Server *s = new Server(solveExpression(commands[index + 1]));
        s->openServer();
        return 2;
    }
};


class ConnectCommand : public Command {

public:
    int execute(vector<string> commands, int index) {
        string IP = commands[index + 1];
        int port = solveExpression(commands[index + 2]);
        Client *c = new Client(IP, port);
        c->openClient();
        return 3;
    }
};


class DefineVarCommand : public Command {

 public:
  int execute(vector<string> commands, int index) {
    if (commands[index+2] == "->") {
      // real value : float value = Singleton::instance()->getInstance().at(commands[index+3]);
      string address = commands[index+4].substr(1);
      address.erase(address.size()-1);
      Singleton::mutex_lock.lock();
      VarToSim::instance()->add(commands[index+1],address ,Singleton::instance()->getInstance().at(address));
      Singleton::mutex_lock.unlock();
    } else if (commands[index+2] == "=") {
        cout<<solveExpression(commands[index+3])<<endl;
      updateVar("ConstVars", commands[index + 1], solveExpression(commands[index+3]));
      return 4;
    } else if (commands[index+2] == "<-") {
       string address = commands[index+4].substr(1);
       address.erase(address.size()-1);
       Vars::instance()->add(commands[index+1], address);
    }
    return 5;
  }
};


class PrintCommand : public Command {
public:
    int execute(vector<string> strings, int index) {
        if(strings[index + 1][0] == '"') {
            string newS = strings[index + 1];
            newS.erase(0,1);
            newS.erase(newS.size() - 1, 1);
            cout << newS << endl;
        } else {
            cout << solveExpression(strings[index + 1]) << endl;
        }
        return 2;
    }
};

class SleepCommand : public Command {
public:
    int execute(vector<string> strings, int index) {
        sleep(solveExpression(strings[index + 1])/1000);
        return 2;
    }
};

class WhileCommand : public Command {
public:
    int execute(vector<string> strings, int index) {
        int indexCopy = index;
        int count = 1;

        unordered_map<string, Command*> commands;
        commands.insert(pair<string, Command*>("openDataServer", new OpenServerCommand()));
        commands.insert(pair<string, Command*>("connectControlClient", new ConnectCommand()));
        commands.insert(pair<string, Command*>("var", new DefineVarCommand()));
        commands.insert(pair<string, Command*>("Sleep", new SleepCommand()));
        commands.insert(pair<string, Command*>("Print", new PrintCommand()));
        commands.insert(pair<string, Command*>("while", new WhileCommand()));

        int pos = index + 5;
        int jumps = index + 6;
        bool hasCommand = false;

        string sign = strings[index + 2];
        string leftStr = strings[index + 1];
        string rightStr = strings[index + 3];


        if (sign == "<") {
            while(solveExpression(leftStr) < solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == ">") {
             while(solveExpression(leftStr) > solveExpression(rightStr)) {
                 int pos = index + 5;
                 while (strings[pos] != "}") {
                     hasCommand = true;
                     if (commands.find(strings[pos]) ==
                         commands.end()) {                                //if not a command
                         string vType = isVar(strings[pos]);
                         if (vType == "no") {  //not var
                             cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                             pos++;
                         } else {                                                                              //is a variable
                             updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                             pos += 3;
                         }
                     } else {                                                                              //is a command
                         Command *c = commands.at(strings[pos]);
                         pos += c->execute(strings, pos);
                     }
                 }
             }



        } else if (sign == "<=") {
            while(solveExpression(leftStr) <= solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == ">=") {
            while(solveExpression(leftStr) >= solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == "==") {
            while(solveExpression(leftStr) == solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == "!=") {
            while(solveExpression(leftStr) != solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }
        }


        while (strings[indexCopy] != "}") {
            indexCopy++;
            count++;
        }

        return count;
    }
};

class IfCommand : public Command {
public:
    int execute(vector<string> strings, int index) {
        int indexCopy = index;
        int count = 1;

        unordered_map<string, Command*> commands;
        commands.insert(pair<string, Command*>("openDataServer", new OpenServerCommand()));
        commands.insert(pair<string, Command*>("connectControlClient", new ConnectCommand()));
        commands.insert(pair<string, Command*>("var", new DefineVarCommand()));
        commands.insert(pair<string, Command*>("Sleep", new SleepCommand()));
        commands.insert(pair<string, Command*>("Print", new PrintCommand()));
        commands.insert(pair<string, Command*>("while", new WhileCommand()));

        int pos = index + 5;
        int jumps = index + 6;
        bool hasCommand = false;

        string sign = strings[index + 2];
        string leftStr = strings[index + 1];
        string rightStr = strings[index + 3];


        if (sign == "<") {
            if(solveExpression(leftStr) < solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == ">") {
            if(solveExpression(leftStr) > solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) ==
                        commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == "<=") {
            if(solveExpression(leftStr) <= solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == ">=") {
            if(solveExpression(leftStr) >= solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == "==") {
            if(solveExpression(leftStr) == solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }



        } else if (sign == "!=") {
            if(solveExpression(leftStr) != solveExpression(rightStr)) {
                int pos = index + 5;
                while (strings[pos] != "}") {
                    hasCommand = true;
                    if (commands.find(strings[pos]) == commands.end()) {                                //if not a command
                        string vType = isVar(strings[pos]);
                        if (vType == "no") {  //not var
                            cout << "Command named : '" << strings[pos] << "' was not defined" << endl;
                            pos++;
                        } else {                                                                              //is a variable
                            updateVar(vType, strings[pos], solveExpression(strings[pos + 2]));
                            pos += 3;
                        }
                    } else {                                                                              //is a command
                        Command *c = commands.at(strings[pos]);
                        pos += c->execute(strings, pos);
                    }
                }
            }
        }


        while (strings[indexCopy] != "}") {
            indexCopy++;
            count++;
        }

        return count;
    }
};


#endif //EX3_COMMAND_H