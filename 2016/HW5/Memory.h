/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.h
 * Author: derya
 *
 * Created on 31 Ekim 2016 Pazartesi, 14:35
 */

#ifndef MEMORY_H
#define MEMORY_H
#define SIZE_OF_ADDRESS 50
#include <iostream>
#include <string>

using namespace std;

class Memory{
public:
    //constructors
    Memory();
    Memory( const int option );
    //setter functions
    void setMemory( const int index, const int value );
    void setMem( const int index, const int value );
    //getter funciton
    const int getMem( const int index ){  return address[index]; }
    //print all the address
    void printAll();
private:
    unsigned int address[ SIZE_OF_ADDRESS ] = {0};
    // option
    int incomingOption;
};

#endif /* MEMORY_H */
