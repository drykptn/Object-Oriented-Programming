/*
 You will rewrite your CPUProgram class so that uses vectors and operator overloading. Your
CPUProgram class has the same pubic member functions as before but now it supports the following
operators
• Operator[] that takes an integer and works like the getLine function. It returns the program
line as a string.
• Operator+ that takes a CPUProgram and an instruction line as a string. It returns a new
CPUProgram that has the original CPUProgram with appended last line from the parameter
string.
• Operator+= that takes an instruction line as a string and appends the instruction to the end of
the program.
• Operator+ that takes two programs and returns a new program that appends the second
programs to the first one
• All comparison operators ==, !=, <, >=, etc. All comparison operators compare the number of
lines of the programs.
• Operator>> that prints the program
• Post and pre decrement operators - - that delete the last line of the program.
• Function call operator() that takes two integers and returns a new program that contains the
instructions between the given integers.
You should keep your instruction strings in a vector<string> data member. You may use any vector
functions as you like.
 */

/* 
 * File:   Computer.cpp
 * Author: derya
 * 
 * Created on 31 Ekim 2016 Pazartesi, 14:35
 */

#include "Computer.h"

Computer::Computer ( ) {/* Empty constructors */}
// set the coming objects to computer object
Computer::Computer (CPU obj1, CPUProgram obj2, Memory obj3, const int option){
    setCPU(obj1);
    setCPUProgram(obj2);
    setMemory(obj3);
    setOption(option);
}
//set the coming option to incoming option
void Computer::setOption ( const int option ) {
    incomingOption = option;
}
//take an option constructor
Computer::Computer ( const int option ){
    setOption(option);
}
//set the coming cpu object to computer object
void Computer::setCPU ( CPU obj1 ) {
    myCPUObj = obj1;
}
//set the coming cpu program object to computer object
void Computer::setCPUProgram ( CPUProgram obj2 ) {
    myCPUProgObj = obj2;
}
//set the coming memory object to computer object
void Computer::setMemory ( Memory obj3 ) {
    myMemoryObj = obj3;
}
void Computer::execute() 
{   
    //command line control
    while( !myCPUObj.halted() )
    {       
        string instruction = myCPUProgObj.getLine( myCPUObj.getPC() );
        if ( incomingOption == 1 || incomingOption == 2 )
            cout << " - " << instruction << " - " << endl;
          myCPUObj.execute( instruction, myMemoryObj );   
//        option controls
        if( incomingOption != 0 ){
            if(incomingOption != 1 ){
                if( incomingOption != 2)
                {
                    cerr << "Invalid option"<< endl;
                    break;
                }
            }
        }
    }
}

