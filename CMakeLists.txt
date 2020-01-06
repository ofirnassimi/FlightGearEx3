cmake_minimum_required(VERSION 3.15)
project(FlightGearEx3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

add_executable(FlightGearEx3 main.cpp Singleton.h Server.h Command.h Client.h Vars.h ConstVars.h toClient.h VarToSim.h BinaryOperator.h Div.cpp Div.h ex1.h Expression.h Interpreter.cpp Interpreter.h Minus.cpp Minus.h Mul.cpp Mul.h Plus.cpp Plus.h UMinus.cpp UMinus.h UnariOperator.cpp UnariOperator.h UPlus.cpp UPlus.h Value.cpp Value.h Variable.cpp Variable.h globFunctions.cpp globFunctions.h ex1.cpp)