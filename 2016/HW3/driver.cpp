/* 
 * File:   driver.c
 * Author: derya
 *
 * Created on 24 Ekim 2016 Pazartesi, 22:18
 */

#include "CPUProgram.h"
#include "CPU.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    CPUProgram myProg(argv[1]);
    CPU myCPU(1);
    //command line control
    if ( argc == 3 ){    
        while( !myCPU.halted() ){
            string instruction = myProg.getLine( myCPU.getPC() );

            if( instruction.rfind(";") >= 0 && instruction.rfind(";") < instruction.size() )
                instruction.erase( instruction.rfind(";") );
                //Change lower case to upper case
            instruction = myCPU.lowerUpper( instruction );

            //if line has any of operation, continue,else fail
            if( instruction.rfind("MOV") >= 0 && instruction.rfind("MOV") < instruction.size() ||
                instruction.rfind("ADD") >= 0 && instruction.rfind("ADD") < instruction.size() ||
                instruction.rfind("SUB") >= 0 && instruction.rfind("SUB") < instruction.size() ||
                instruction.rfind("JMP") >= 0 && instruction.rfind("JMP") < instruction.size() ||
                instruction.rfind("HLT") >= 0 && instruction.rfind("HLT") < instruction.size() ||
                instruction.rfind("PRN") >= 0 && instruction.rfind("PRN") < instruction.size() ){
                //option control
                if( *argv[2] == '0' || *argv[2] == '1' ){
                    // clean string from space
                    instruction = myCPU.eraseSpace( instruction );
                    myCPU.execute(instruction);
                    if( *argv[2] == '1' )
                        myCPU.print();
                }
                else{
                    cerr << "Wrong option! Error!" << endl;
                    return 0;
                }
            }
            else{
                //if user write a wrong type, fail and out of the loop
                cerr << "Syntax error!" << endl;
                return 0;
                // condition out of the loop
            }
        }
    }
    else{
        cerr << "Wrong command line!" << endl;
        return 0;
    }
    return 0;
}
