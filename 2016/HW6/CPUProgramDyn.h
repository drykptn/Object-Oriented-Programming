/* 
 * File:   CPUProgramDyn.h
 * Author: derya
 *
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#ifndef CPUPROGRAMDYN_H
#define CPUPROGRAMDYN_H
#include <iostream>
#include <string>
#include <fstream>
#include <new>

using namespace std;

namespace zeytin
{
    class CPUProgramDyn {
    public:
        //constructors
        CPUProgramDyn();
        CPUProgramDyn( const string filename );
        CPUProgramDyn( const int option );
        CPUProgramDyn( const CPUProgramDyn& obj );
        ~CPUProgramDyn();
        void findSize( const string filename );
        void setFilename( const string filename );
        void setNumberOfLines( const int num );
        string getFilename();
        void setFile( const int size, const string line );
        // function takes a string file name as a parameter, reads the program file 
        // and stores all the program instructions
        void ReadFile( const string filename );
        //function takes an integer as the parameter and returns a string that 
        //contains the program line that corresponds to the integer
        const string getLine( const int currentLine )const;
        //function re1turns the number of lines read from the file
        int size();
        //void tempSizeFile( int num );
        string testAddOver( const string line );
        string & operator []( const int size );
        const CPUProgramDyn operator--(); //prefix decrement
        const CPUProgramDyn operator--( int ); //postfix decrement
        bool operator == ( CPUProgramDyn& other );
        bool operator != ( CPUProgramDyn& other );
        bool operator < ( CPUProgramDyn& other );
        bool operator > ( CPUProgramDyn& other );
        bool operator <= ( CPUProgramDyn& other );
        bool operator >= ( CPUProgramDyn& other );
        CPUProgramDyn operator + ( const string line );
        CPUProgramDyn operator + ( CPUProgramDyn& other );
        CPUProgramDyn& operator =( const CPUProgramDyn& obj );
        CPUProgramDyn operator += ( const string line );
        CPUProgramDyn operator () ( const int num1, const int num2 );
        friend ostream &operator<<( ostream& output, CPUProgramDyn obj );
    private:
        string *fileStr = NULL;
        // size of file
        int numberOfLines;
        // option
        int incomingOption;
        string filename;
        int tempNumberOfLine = 0;
    };
}
#endif /* CPUPROGRAMDYN_H */