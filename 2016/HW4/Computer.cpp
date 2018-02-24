/*
This homework will be very similar to HW2, only it will use OOP techniques such as composition.
You will design and implement new classes.
First, you will design and implement a class for a Memory . Your memory can hold 50 unsigned
integers as in HW2. The addreses start from 0. Your memory class has getter and setter functions for
memory locations.
Modify your CPU class of HW3 so that your CPU can now handle memory instructions as listed in
HW2. Modify your execute function of your CPU class so that it takes an intruction as a string and a
memory object. For example,
myCPU.execute(“MOV R1, #45”, myMemory)
moves the value of R1 into the memory location 45 in myMemory .
Write another class named Computer . This class will have objects of CPU , Memory and CPUProgram as
its data members. It has all necessary constructors and setter/getters. The class Computer has a
function named execute which takes a program file name and an integer option. It then executes loads
program and executes it on the CPU using computers memory.
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
        //option controls
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

