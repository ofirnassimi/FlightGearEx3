#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "Command.h"

std::mutex Singleton::mutex_lock;

using namespace std;

vector<string> lexer(string fname) {
    fstream f;
    f.open(fname, ios::in | ios::out);
    vector<string> strings(0);

    if (f) {
        string line;
        char c = '"';
        while (getline(f, line)) {
            int i;
            string command;
            for (i = 0; i < line.length(); i++) {
                command = "";
                while ((line[i] != ',') && (line[i] != '(') && (line[i] != ' ') && (line[i] != ')') &&
                       (line[i] != '\t') && (i < line.length())) {
                    if ((strings.size() > 0) && (strings[strings.size() - 1] == "Print") && (line[i] == '"')) {
                        strings.resize(strings.size() + 1);
                        command = line.substr(i);
                        command.erase(command.size() - 1);
                        strings[strings.size() - 1] = command;
                        line[i + 1] = ',';
                        command = "";
                        i = line.length();
                    } else {
                        command += line[i];
                    }
                    i++;
                }
                if (command != "") {
                    strings.resize(strings.size() + 1);
                    strings[strings.size() - 1] = command;
                    if (command == "=") {
                        strings.resize(strings.size() + 1);
                        command = line.substr(line.find("=") + 2);
                        strings[strings.size() - 1] = command;
                        i = line.length();
                    }
                }
            }
        }
        f.close();
    } else {
        cout<<"could not open file"<<endl;
    }
    return strings;
}

void parser(vector<string> strings, unordered_map<string, Command*> commands) {
  int index = 0;
  while (index < strings.size()) {
      if (commands.find(strings[index]) == commands.end()) {                                //if not a command
          string vType = isVar(strings[index]);
          if (vType == "no") {  //not var
              cout << "Command named : '" << strings[index] << "' was not defined" << endl;
              index++;
          } else {                                                                              //is a variable
              updateVar(vType, strings[index], solveExpression(strings[index + 2]));
              index += 3;
          }
      } else {                                                                              //is a command
          Command *c = commands.at(strings[index]);
          index += c->execute(strings, index);
      }
  }
}

unordered_map<string, Command*> createMap() {
  unordered_map<string, Command*> commands;

  commands.insert(pair<string, Command*>("openDataServer", new OpenServerCommand()));
  commands.insert(pair<string, Command*>("connectControlClient", new ConnectCommand()));
  commands.insert(pair<string, Command*>("var", new DefineVarCommand()));
  commands.insert(pair<string, Command*>("Sleep", new SleepCommand()));
  commands.insert(pair<string, Command*>("Print", new PrintCommand()));
  commands.insert(pair<string, Command*>("while", new WhileCommand()));
  commands.insert(pair<string, Command*>("if", new IfCommand()));

  return commands;
}

int main(int argc, char * argv[]) {
  unordered_map<string, Command *> commands = createMap();
  vector<string> strings = lexer(argv[1]);
  parser(strings, commands);
    while (true) {

    }

}