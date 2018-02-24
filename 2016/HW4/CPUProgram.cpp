/* 
 * File:   CPUProgram.cpp
 * Author: derya
 * 
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#include "CPUProgram.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

CPUProgram::CPUProgram ( ):numberOfLines(0) {/* Empty constructor */}
// take an option constructor
CPUProgram::CPUProgram (const int option ) :incomingOption(option){}
//This function read the file and find the size of file
const int CPUProgram::ReadFile(const string filename){
    string line;
    fstream input;
    input.open(filename);
    if( input.is_open() )
    {
        //to find number of line in file
        while( !input.eof() )
        {
            getline( input, line ); // read a line by line from file   		
            fileStr[numberOfLines] = line; // and put the line a string array
            numberOfLines++;
        }
    }
    else //file could not be opened
        cerr << "File could not be opened." << endl;
    input.close();    
    return numberOfLines;
}
// take a size, and return that line from file
const string CPUProgram::getLine( const int currentLine ){
    return fileStr[currentLine ];
}
//return size of file
const int CPUProgram::size(){
    return numberOfLines;
}