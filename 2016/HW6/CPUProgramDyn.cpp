/* 
 * File:   CPUProgramDyn.cpp
 * Author: derya
 * 
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#include "CPUProgramDyn.h"
#include "CPU.h"

namespace zeytin{

    CPUProgramDyn::CPUProgramDyn( const string filename ):numberOfLines(0){
        ReadFile(filename);
    }

    CPUProgramDyn::CPUProgramDyn ():numberOfLines(0)
    {/* Empty constructor */}

    // take an option constructor
    CPUProgramDyn::CPUProgramDyn (const int option ) 
    :numberOfLines(0), incomingOption(option) {/**/}
    
    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& obj)
    : incomingOption(obj.incomingOption), filename( obj.filename ),
      numberOfLines( obj.numberOfLines )
    {
        if( numberOfLines!= 0 ){
            fileStr = new string[ numberOfLines ];
            for ( int i = 0; i < numberOfLines; i++ )
                fileStr[i] = obj.fileStr[i];   
        }
    }

    CPUProgramDyn::~CPUProgramDyn ( ) {
        if( fileStr ){
          delete [] fileStr;
          fileStr = nullptr;
        }
    }
    
    void CPUProgramDyn::setFilename ( const string fileName ) {
        filename = fileName;
    }

    void CPUProgramDyn::setNumberOfLines ( const int num ) {
        numberOfLines = num;
    }

    string CPUProgramDyn::getFilename ( ) {
        return filename;
    }
    void CPUProgramDyn::setFile ( const int i, const string line ) {
        fileStr[i] += line;
    }

    void CPUProgramDyn::findSize ( const string filename ) {
        setFilename(filename);
        string line;
        fstream input;
        input.open(getFilename());
        if( input.is_open() )
        {
            //to find number of line in file
            while( !input.eof() )
            {
                getline( input, line ); // read a line by line from file   		
                numberOfLines++;
            }
        }
        else //file could not be opened
            cerr << "File could not be opened." << endl;
        input.close();    
    }

    ////This function read the file and find the size of file
    void CPUProgramDyn::ReadFile(const string filename){
        findSize( filename );
        string line;
        fstream input;
        input.open(getFilename());       
        if( input.is_open() )
        {
            fileStr = new string[numberOfLines]; 
            for ( int i = 0; i < numberOfLines; i++ ) {
                getline( input , line);
                setFile( i, line );
            }
            
        }
    }
    // take a size, and return that line from file
    const string CPUProgramDyn::getLine( const int currentLine )const{
        return fileStr[currentLine ];
    }
    //return size of file
    int CPUProgramDyn::size(){ 
        return numberOfLines;
    }
    // overloading function for operator[]
    string& CPUProgramDyn::operator[] ( const int size ) {
        if( size >= this->size() )
            cerr << "Invalid size" << endl;
        return fileStr[size];
    }
    // prefix decrement
    const CPUProgramDyn CPUProgramDyn::operator-- () {
        //delete the last line from vector
        CPUProgramDyn temp;
        temp.setNumberOfLines( this->size() );
        temp.fileStr = new string [ temp.size() ];
        for ( int i = 0; i < this->size() ; i++ )
            temp.setFile( i, this->getLine(i) );
        
        delete [] fileStr;
        fileStr = nullptr;
        this->setNumberOfLines( size() );
        fileStr = new string [ size() ];
        for ( int i = 0; i < size() ; i++ )
            setFile( i, temp.getLine(i) );
        return *this;
    }
    // postfix decrement
    const CPUProgramDyn CPUProgramDyn::operator-- ( int ) {
        CPUProgramDyn temp;
        temp.fileStr = new string[ numberOfLines ];
        for ( int i = 0; i < this->size() ; i++ )
            temp.setFile( i, getLine(i) );
        delete [] fileStr;
        fileStr = nullptr;
        this->setNumberOfLines( size()-1 );
        fileStr = new string [ size() ];
        for ( int i = 0; i < this->size() ; i++ )
            setFile( i, temp.getLine(i) );
        return temp;
    }
    // overloading function for assignment operator
    bool CPUProgramDyn::operator== ( CPUProgramDyn& other)  {
        return ( size() == other.size() );
    }
    // overloading function for not equal operator
    bool CPUProgramDyn::operator!= ( CPUProgramDyn& other) {
        return ( !( size() == other.size() ) );
    }
    // overloading function for compare operator
    bool CPUProgramDyn::operator< ( CPUProgramDyn& other) {
        if( size() < other.size() )
            return true;
        else if ( size() == other.size() && size() < other.size() )
            return true;
    }
    // overloading function for compare operator
    bool CPUProgramDyn::operator> ( CPUProgramDyn& other) {
        if( size() > other.size() )
            return true;
        else if ( size() == other.size() && size() > other.size() )
            return true;
    }
    // overloading function for compare operator
    bool CPUProgramDyn::operator>= (CPUProgramDyn& other) {
        if( size() >= other.size() )
            return true;
        else if ( size() == other.size() && size() >= other.size() )
            return true;
    }
    // overloading function for compare operator
    bool CPUProgramDyn::operator<= (CPUProgramDyn& other) {
        if( size() <= other.size() )
            return true;
        else if ( size() == other.size() && size() <= other.size() )
            return true;
    }
    // overloading function for cout operator
    ostream &operator<< (ostream& output , CPUProgramDyn obj ) {
        for ( int i = 0; i < obj.size() ; i++ ) 
            output << obj.fileStr[i] << endl;
        return output;    
    }

    string CPUProgramDyn::testAddOver ( const string line ) {
        if( line == "" ){
            cerr << "You can't add a empty string" << endl;
            return "";
        }
    }

    // overloading function for add += operator
    CPUProgramDyn CPUProgramDyn::operator+= ( const string line ) {
        // if user send a empty line to vector
        string test;
        test = testAddOver( line );
        if ( test != "" ){
            CPUProgramDyn temp;
            int num = size();

            temp.fileStr = new string[num+1];

            for ( int i = 0; i < num ; i++ )
                temp.setFile( i, this->fileStr[i] );

            delete [] this->fileStr;
            this->fileStr = nullptr;
            this->fileStr = new string[num+1];

            for ( int i = 0; i < num ; i++ )
                this->setFile( i, temp.getLine(i) );

            this->setFile( num, line );
            setNumberOfLines(num+1);
            return *this;
        }
    }
    CPUProgramDyn& CPUProgramDyn::operator =(const CPUProgramDyn& obj){
        if( &obj != this ){
            numberOfLines = obj.numberOfLines;
            incomingOption = obj.incomingOption;
            filename = obj.filename;
            delete [] fileStr;
            fileStr = nullptr;
            fileStr = new string[ obj.numberOfLines ];
            for ( int i = 0; i < obj.numberOfLines ; i++ )
                fileStr[i] = obj.fileStr[i];
        }
        return *this;
    }
     //overloading function for add operator
    CPUProgramDyn CPUProgramDyn::operator+ ( const string line ) {
        string test;
        test = testAddOver( line );
        if( test != ""){
            CPUProgramDyn newObj;
            int num = this->size();
            newObj.numberOfLines = num+1;
            newObj.fileStr= new string[ newObj.size() ];
            for ( int i = 0; i < num ; i++ )
                newObj.setFile(i, this->fileStr[i]);
            newObj.setFile( num, line);
            newObj.setNumberOfLines( num+1 );
            
            return newObj;
        }
    }
    // overloading function for add operator
    CPUProgramDyn CPUProgramDyn::operator+ ( CPUProgramDyn& other ) {
        CPUProgramDyn temp;
        int num1 = size();
        int num2 = other.size();
        temp.setNumberOfLines( num1+num2 );
        temp.fileStr = new string [ temp.size() ];
        for ( int i = 0; i < num1 ; i++ )
            temp.setFile( i, getLine(i) );
        int j=0;
        for ( int i = num1; i < temp.size() ; i++ )
        {
            temp.setFile( i, other.getLine(j) );
            j++;
        }
        return temp;
    }
    // overloading function for function call() operator
    CPUProgramDyn CPUProgramDyn::operator() ( const int num1 , const int num2 )  {
        // error check
        if ( num1 > num2 ){
            cerr << "First num should smaller than second num" << endl;
            return *this;
        }
        else if ( num1 < 0 || num1 > size() || num2 < 0 || num2 > size() ){
            cerr << "Numbers can't bigger than string size" << endl;
            return *this;
        }
        // takes line from string and add  of temp
        CPUProgramDyn temp;
        temp.setNumberOfLines( num2-num1+1 );
        temp.fileStr = new string [ temp.size() ];
        int j=0;
        for ( int i = num1 ; i <= num2; i++ )
        {
            temp.setFile( j, this->fileStr[i] );
            j++;
        }
        return temp;
    }    
}