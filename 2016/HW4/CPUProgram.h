
/* 
 * File:   CPUProgram.h
 * Author: derya
 *
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#define SIZE_OF_FILE 200
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class CPUProgram {
public:
    //constructors
    CPUProgram();
    CPUProgram( const int option );
    // function takes a string file name as a parameter, reads the program file 
    // and stores all the program instructions
    const int ReadFile( const string filename );
    //function takes an integer as the parameter and returns a string that 
    //contains the program line that corresponds to the integer
    const string getLine( const int currentLine );
    //function returns the number of lines read from the file
    const int size();   
private:
    string fileStr[SIZE_OF_FILE];
    // size of file
    int numberOfLines;
    // option
    int incomingOption;
};

#endif /* CPUPROGRAM_H */
