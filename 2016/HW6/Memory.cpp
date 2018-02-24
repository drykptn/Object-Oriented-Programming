/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Memory.cpp
 * Author: derya
 * 
 * Created on 31 Ekim 2016 Pazartesi, 14:35
 */

#include "Memory.h"

Memory::Memory ( ){/*Empty constructor*/ }
// take an option constructor
Memory::Memory( const int option ):incomingOption(option){}
//set the memory for null value
void Memory::setMemory ( const int index , const int value ) {
    address[index] = 0;
}
//set the memory for incoming value
void Memory::setMem ( const int index , const int value ) {
    address[index] += value;
}

//print memory on the screen
void Memory::printAll ( ) 
{
    cout << "Memory Values" << endl;
   
    for (int i = 0; i < SIZE_OF_ADDRESS  ;  ++i)
    {
        cout << "#" << i << " : " << address[i] << " | ";
        if( i == 9 || i == 19 || i == 29 || i == 39 )
            cout << endl;
    }
    cout << endl;
}