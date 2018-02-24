/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Computer.h
 * Author: derya
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:35
 */

#ifndef COMPUTER_H
#define COMPUTER_H
#include <iostream>
#include <string>
#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

using namespace std;

class Computer{
public:
    //constructors
    Computer();
    Computer( CPU obj1, CPUProgram obj2, Memory obj3, const int option );
    Computer( const int option );
    //setter functions
    void setCPU( CPU obj1 );
    void setCPUProgram(CPUProgram obj2);
    void setMemory(Memory obj3);
    void setOption( const int option );
    //getter functions
    const CPU getCPU(){ return myCPUObj; }
    const CPUProgram getCPUProgram(){ return myCPUProgObj; }
    const Memory getMemory(){ return myMemoryObj; }
    //loads program and executes it on the CPU using computers memory
    void execute();
private:
    //objects
    CPUProgram myCPUProgObj;
    CPU myCPUObj;
    Memory myMemoryObj;
    //optioon
    int incomingOption;  
};

#endif /* COMPUTER_H */