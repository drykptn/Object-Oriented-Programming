
/* 
 * File:   CPUProgram.h
 * Author: derya
 *
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H
#include <iostream>
#include <string>
#include <fstream>
#define SIZE_OF_FILE 200

using namespace std;

class CPUProgram {
public:
    // function takes a string file name as a parameter, reads the program file 
    // and stores all the program instructions
    const int readFile(string filename);
    CPUProgram(string filename); 
    //function takes an integer as the parameter and returns a string that 
    //contains the program line that corresponds to the integer
    const string getLine( int currentLine );
    //function returns the number of lines read from the file
    const int size();
    string fileStr[SIZE_OF_FILE];
private:
    int numberOfLines = 0;
};

#endif /* CPUPROGRAM_H */

