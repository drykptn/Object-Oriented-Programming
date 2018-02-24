/* 
 * File:   driver.c
 * Author: derya
 *
 * This homework be very similar to HW2, only I used OOP techniques such as 
 * composition.
 * I designed and implement new classes.
 */
#include "Computer.h"
#include "CPUProgram.h"
#include "CPU.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


int main(int argc, char** argv){
    if( argc != 3 )
    {
        cerr << "Invalid command" << endl;
        return 0;
    }
    const char* filename = argv[1];
    CPU myCPU(myCPU.convertInteger( argv[2]) );    
    int option = myCPU.convertInteger(argv[2]);   
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);    
    Memory myMemory;    
    Computer myComputer1(myCPU, myCPUProgram, myMemory, option);    
    myMemory.setMem(0, 100); 
    cout << myMemory.getMem(0) << endl;
    myMemory.printAll();
    myCPU.execute("MOV #0, R1", myMemory); 
    myCPU.execute("MOV R1, #1", myMemory);
    cout << myCPUProgram.getLine(0) << endl; 
    cout << myCPUProgram.getLine(myCPUProgram.size()-2) << endl;
    Computer myComputer2(option); 
    myComputer2.setCPU(
    myComputer1.getCPU() );
    myComputer2.setCPUProgram(myComputer1.getCPUProgram() );
    myComputer2.setMemory(myComputer1.getMemory() ); 
    myComputer2.execute();
    return 0;
}
