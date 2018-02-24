
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
#include <vector>

using namespace std;


class CPUProgram {
public:
    //constructors
    CPUProgram();
    CPUProgram( const int option );
    void setVector( string line );
    // function takes a string file name as a parameter, reads the program file 
    // and stores all the program instructions
    const int ReadFile( const string filename );
    //function takes an integer as the parameter and returns a string that 
    //contains the program line that corresponds to the integer
    const string getLine( const int currentLine )const;
    //function returns the number of lines read from the file
    const int size();
    string & operator []( int size );
    vector<string> operator--(); //prefix decrement
    vector<string> operator--( int ); //postfix decrement
    bool operator == ( CPUProgram& other );
    bool operator != ( CPUProgram& other );
    bool operator < ( CPUProgram& other );
    bool operator > ( CPUProgram& other );
    bool operator <= ( CPUProgram& other );
    bool operator >= ( CPUProgram& other );
    CPUProgram operator + ( string line );
    CPUProgram operator + ( CPUProgram& other );
    vector<string> operator += ( string line );
    CPUProgram operator () ( int num1, int num2 );
    friend ostream &operator<<( ostream& output, CPUProgram obj );
private:
    vector < string > fileStr;   
    // size of file
    int numberOfLines;
    // option
    int incomingOption;
};

#endif /* CPUPROGRAM_H */
