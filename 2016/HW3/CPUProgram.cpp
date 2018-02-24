/* 
 * File:   CPUProgram.cpp
 * Author: derya
 * 
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#include "CPUProgram.h"

CPUProgram::CPUProgram( string filename ){
    readFile(filename);
}
const int CPUProgram::readFile(string filename){
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
const string CPUProgram::getLine(int currentLine){
    return fileStr[currentLine ];
}
const int CPUProgram::size(){
    return numberOfLines;
}