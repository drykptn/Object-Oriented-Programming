/* 
 * File:   CPU.h
 * Author: derya
 *
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#ifndef CPU_H
#define CPU_H
#define SIZE_OF_REGISTER 5
#include "Memory.h"
#include <iostream>
#include <string>

using namespace std;

class CPU{
public:
    //constructors
    CPU();
    CPU( int option );
    //setter functions
    void setRegister( const int size, const int value );
    void setPC( const int num );
    void setReg( const int size, const int value );
    //getter functions
    const int getRegister(const int size);
    const int getPC();
    //This function print registers and PC on screen
    void prn(  string secondValueString, Memory& myMemoryObj );
    //function returns true if the last instruction executed halted the CPU
    bool halted();
    //This function takes a line and executes it and advances the PC accordingly
    const int execute( string line, Memory& myMemoryObj );
    //This function controls values of memory
    const int controlUnsignedAddress( Memory& myMemoryObj );
    //This function makes copy
    const Memory move( const int result1,const int result2 , 
                       string secondValueString, string lastValueString, 
                       Memory& myMemoryObj );
    //This function makes addition
    const Memory add( const int result1, const int result2 ,
                      const string secondValueString, string lastValueString, 
                      Memory& myMemoryObj );
    //This function makes subtraction
    const Memory sub( const int result1, const int result2 , 
                      const string secondValueString, string lastValueString, 
                      Memory& myMemoryObj );
    //This function control number and when needed its change line
    int jmp( const string secondValueString, const string lastValueString, 
             const int jumpNum);
    //This function control number and when needed its change line
    int jpn( const string secondValueString, const string lastValueString);
    //This function erase space from string
    const string eraseSpace( string line );
    // This function converts lower letters to upper letters
    const string lowerUpper( string line );
    // This function find register name
    const int findRegister( string line );
    //This function convert a string to integer
    const int convertInteger( const string str );
    //This function controls strings to register or number
    const int controlRegisterOrNumber( const string str );
    //print all the registers
    void print();
    //This function controls incoming instruction what is
    int controlRegisterOrNumberOrAddress( const string str );
private:
    int registerArray[SIZE_OF_REGISTER]= {0};
    int PC;
    //firs string from instruction
    string operation;
    //option
    int incomingOption;
};
#endif /* CPU_H */