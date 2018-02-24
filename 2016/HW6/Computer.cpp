/*
You will rewrite your CPUProgram of HW5 class so that uses dynamic memory. Your new
CPUProgramDyn class has the same public member functions and overloaded operators. Therefore
the customers of your class will not see any difference. However, your new class will not use any
vectors and it has to allocate and deallocate its memory as required.
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
Computer::Computer (CPU obj1, CPUProgramDyn obj2, Memory obj3, const int option){
    setCPU(obj1);
    setCPUProgramDyn(obj2);
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
void Computer::setCPUProgramDyn ( CPUProgramDyn obj2 ) {
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

