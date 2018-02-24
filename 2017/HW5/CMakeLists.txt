cmake_minimum_required(VERSION 3.8)
project(hw5)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Cell.h ConnectFourAbstract.h ConnectFourPlus.cpp ConnectFourPlus.h ConnectFourDiag.cpp ConnectFourDiag.h ConnectFourPlusUndo.cpp ConnectFourPlusUndo.h ConnectFourAbstract.cpp)
add_executable(hw5 ${SOURCE_FILES})