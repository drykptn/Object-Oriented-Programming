/* 
This homework will be very similar to HW1, only it will use OOP techniques.
First, you will design and implement a class for a CPU that has 5 registers (R1, R2, R3, R4, R5) and
no other memory. Your CPU also has a special register PC (program counter) that keeps the current
program line number that it executes. All registers are initialized to zero (PC is 1 ) when the CPU
objects are formed. Your CPU class should have functions for
• Appropriate constructor(s)
• Setters and getters for all registers and PC
• print function that prints all the registers and the PC
• halted function returns true if the last instruction executed halted the CPU.
• execute function takes a string that contains an instruction line, executes it and advances
the PC accordingly. For example, myCPU.execute(“MOV R1, 100”) puts the value of 100 to
the register 1.
The instruction set for your CPU class will be the exactly the same as HW1.
Second, you will design and implement another class for a CPU program. Your CPUProgram will
have the following member functions:
• ReadFile function takes a string file name as a parameter, reads the program file and stores
all the program instructions.
• A constructor that takes a file name as parameter and calls the functions readFile.
• getLine function takes an integer as the parameter and returns a string that contains the
program line that corresponds to the integer.
• size function returns the number of lines read from the file.
Your main function will make one CPUProgram object and one CPU object. The file name and the run
time options will come from the command line as in HW1. You will use getLine function of
CPUProgram to get the program lines and use the execute function of CPU objects to execute the
lines.
 * File:   CPU.h
 * Author: derya
 *
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#ifndef CPU_H
#define CPU_H
#define SIZE_OF_REGISTER 5
#include <iostream>
#include <string>

using namespace std;

class CPU{
public:
    CPU( int num );
    void setRegister( int size, int value );
    void setPC( int num );
    int getRegister();
    int getPC();
    //This function print registers and PC on screen
    void prn( string secondValueString );
    //function returns true if the last instruction executed halted the CPU
    bool halted();
    //This function takes a line and executes it and advances the PC accordingly
    int execute( string line );
    //This function makes copy
    void move( int result1, int result2 , string secondValueString, 
              string lastValueString );
    //This function makes addition
    void add(int result1, int result2 , string secondValueString, 
            string lastValueString );
    //This function makes subtraction
    void sub(int result1, int result2 , string secondValueString, 
            string lastValueString );
    //This function control number and when needed its change line
    int jmp( string secondValueString, string lastValueString, int jumpNum);
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
    void print();
private:
    int registerArray[SIZE_OF_REGISTER]= {0};
    int PC;
    string operation;
};
#endif /* CPU_H */

