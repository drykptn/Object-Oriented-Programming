/* 
 * File:   CPUProgram.cpp
 * Author: derya
 * 
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#include <stdlib.h>

#include "CPUProgram.h"

CPUProgram::CPUProgram ( ):numberOfLines(0) {/* Empty constructor */}
// take an option constructor
CPUProgram::CPUProgram (const int option ) 
:numberOfLines(0), incomingOption(option) {/**/}

void CPUProgram::setVector ( string line ) {
    // erase the comment of file
    if( line.rfind(";") >= 0 && line.rfind(";") < line.size() )
        line.erase( line.rfind(";") );
    fileStr.push_back( line );
}

//This function read the file and find the size of file
const int CPUProgram::ReadFile(const string filename){
    string line;
    fstream input;
    input.open("file.txt");
    if( input.is_open() )
    {
        //to find number of line in file
        while( !input.eof() )
        {
            getline( input, line ); // read a line by line from file   		
            setVector( line ); // and put the line a string array
            numberOfLines++;
        }
    }
    else //file could not be opened
        cerr << "File could not be opened." << endl;
    input.close();    
    return numberOfLines;
}
// take a size, and return that line from file
const string CPUProgram::getLine( const int currentLine )const{
    return fileStr[currentLine ];
}
//return size of file
const int CPUProgram::size(){
    return fileStr.size();
}
// overloading function for operator[]
string& CPUProgram::operator[] ( int size ) {
    if( size >= fileStr.size() )
        cerr << "Invalid size" << endl;
    return fileStr[size];
}
// prefix decrement
vector<string> CPUProgram::operator-- () {
    //delete the last line from vector
    fileStr.pop_back();
    return fileStr;
}
// postfix decrement
vector<string> CPUProgram::operator-- ( int ) {
    // create a temporary vector
    vector <string> temp;
    // copy the orijinal vector to temporary vector
    temp = fileStr;
    // delete the last line from orijinal vector
    fileStr.pop_back();
    return temp;
}
// overloading function for assignment operator
bool CPUProgram::operator== ( CPUProgram& other) {
    return ( size() == other.size() );
}
// overloading function for not equal operator
bool CPUProgram::operator!= ( CPUProgram& other) {
    return ( !( size() == other.size() ) );
}
// overloading function for compare operator
bool CPUProgram::operator< ( CPUProgram& other) {
    if( size() < other.size() )
        return true;
    else if ( size() == other.size() && size() < other.size() )
        return true;
}
// overloading function for compare operator
bool CPUProgram::operator> ( CPUProgram& other) {
    if( size() > other.size() )
        return true;
    else if ( size() == other.size() && size() > other.size() )
        return true;
}
// overloading function for compare operator
bool CPUProgram::operator>= (CPUProgram& other) {
    if( size() >= other.size() )
        return true;
    else if ( size() == other.size() && size() >= other.size() )
        return true;
}
// overloading function for compare operator
bool CPUProgram::operator<= (CPUProgram& other) {
    if( size() <= other.size() )
        return true;
    else if ( size() == other.size() && size() <= other.size() )
        return true;
}
// overloading function for cout operator
ostream &operator<< (ostream& output , CPUProgram obj ) {
    for ( int i = 0; i < obj.size() ; i++ ) 
        output << obj.getLine(i) << endl;
    return output;    
}
// overloading function for add += operator
vector<string> CPUProgram::operator+= ( string line ) {
    // if user send a empty line to vector
    if( line == "" ){
        cerr << "You can't add a empty string" << endl;
        return fileStr;
    }
    // add line to vector
    fileStr.push_back( line );
    return fileStr;
}
// overloading function for add operator
CPUProgram CPUProgram::operator+ ( string line ) {
    if( line == "" ){
        cerr << "You can't add a empty string" << endl;
        return *this;
    }
    else if( line != ""){
        CPUProgram newObj;
        newObj.fileStr = fileStr;
        newObj.setVector( line );       
        return newObj;
    }
}
// overloading function for add operator
CPUProgram CPUProgram::operator+ ( CPUProgram& other ) {
    CPUProgram temp;
    for ( int i = 0; i < this->size(); i++ )
        temp.setVector( getLine(i) );
    for ( int i = 0; i < other.size(); i++ )
        temp.setVector( other.getLine(i) );
 
    return temp;
}
// overloading function for function call() operator
CPUProgram CPUProgram::operator() ( int num1 , int num2 ) {
    CPUProgram temp;
    // error check
    if ( num1 > num2 )
        cerr << "First num should smaller than second num" << endl;
    else if ( num1 < 0 || num1 > fileStr.size() || num2 < 0 || num2 > fileStr.size() )
        cerr << "Numbers can't bigger than vector size" << endl;
    // takes line from vector and add vector of temp
    for ( int i = num1; i <= num2; i++ )
        temp.setVector( this->getLine(i) );
    return temp;
}