
/* 
 * File:   CPU.cpp
 * Author: derya
 * 
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#include "CPU.h"

CPU::CPU ( int num ) {
    setPC( num-1 );
}
void CPU::setRegister( int size, int value ){
    registerArray[size] += value;
}
void CPU::setPC( int num ){
    PC = num;
}
int CPU::getRegister(){
    return *registerArray;
}
int CPU::getPC(){
    return PC;
}
bool CPU::halted(){
    if( operation.compare("HLT") == 0 )
        return true;
    else
        return false;
}
void CPU::print()
{
    //print all the register on screen
    for (int i = 0; i < SIZE_OF_REGISTER ; ++i)
            cout << "R" << i+1 << " : " << registerArray[i] << endl;
    cout << "PC : " << PC+1 << endl;
}
int CPU::execute(string instruction){
    string secondValueString, lastValueString;
    int i, j, currentLine;    
    int result1 = 0, result2 = 0, value = 0;
    //takes operation name from line string
    for (int k = 0; k < 3 ; ++k)
        operation += instruction[k];
    //then erase operation from string
    instruction.erase( 0, 3 );
    //if instruction has "," , continue
    if( instruction.rfind(",") >= 0 && instruction.rfind(",") <= instruction.size() )
    {
        //read till ",", and put a another string
        for ( i = 0; instruction[i] != ',' ; ++i)
            secondValueString += instruction[i];
        //read rest of them till size of instruction
        for ( j = i + 1 ; j < instruction.size(); ++j)
            lastValueString += instruction[j]; 		
    }// for JMP constant 
    else
    {
        //read till size of instruction and put a another string
        for ( i = 0; i < instruction.size() ; ++i)
            secondValueString += instruction[i];
    }
    //check control string what is register or number
    //and if it is a register, return 1, else return 2
    result1 = controlRegisterOrNumber( secondValueString );
    result2 = controlRegisterOrNumber( lastValueString );
    //if operation is "MOV",continue
    if( operation.compare("MOV") == 0 )
        move( result1 , result2, secondValueString, lastValueString );
    //if operation is "ADD",continue
    else if( operation.compare("ADD") == 0 )
       add(result1 , result2, secondValueString, lastValueString );
    //if operation is "SUB",continue
    else if( operation.compare("SUB") == 0 )
        sub( result1, result2 , secondValueString,lastValueString );
    //if operation is "JMP",continue
    else if( operation.compare("JMP") == 0 )
    {	
        //check control string what is register or number
        value = controlRegisterOrNumber( secondValueString );
        //if string is a register
        if ( value == 1 )		       
            currentLine = jmp( secondValueString, lastValueString, 1 );
        //if string is a number
        else if ( value == 2 )
            currentLine = jmp( secondValueString, lastValueString, 2 );	
        
        setPC( currentLine );
    }
    else if( operation.compare("PRN") == 0 )
        prn( secondValueString );                 
    //if operation is "HLT",continue
    else if( operation.compare("HLT") == 0 )
    {
        //go to hlt function and finish the program
        print();
        return 0;
    }
    operation.erase(0);
    secondValueString.erase(0);
    lastValueString.erase(0);
    PC++;
}
// This function makes move
void CPU::move( int result1, int result2 , string secondValueString, 
               string lastValueString) 
{
    //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
        //find the register name 
        int size = findRegister( secondValueString );
        //convert the string to integer
        int lastNum = convertInteger( lastValueString );
        //then copy th number to the register
        setRegister( size, 10 );
    }
    //if secondValueString and lastValueString are registers 
    else if ( result1 == 1 && result2 == 1 )
    {
        //find the register name
        int size1 = findRegister( secondValueString );
        //find the register name
        int size2 = findRegister( lastValueString );
        //be sure whether or not register is empty 
        setRegister( size2, 0 );
        //then copy 
        setRegister( size2, registerArray[size1]);
    }			
}
// This function makes add
void CPU::add(int result1, int result2 , string secondValueString, 
             string lastValueString)
{
    //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
        //find the register name 
        int size = findRegister( secondValueString );
        //convert the string to integer
        int lastNum = convertInteger( lastValueString );
        // add number to register
        setRegister( size, lastNum );
    }
    //if secondValueString and lastValueString are registers 
    else if ( result1 == 1 && result2 == 1 )
    {
        //find the register name
        int size1 = findRegister( secondValueString );
        //find the register name
        int size2 = findRegister( lastValueString );
        //add register2 to register1
        setRegister( size1, registerArray[size2]);
    }	
}
// This function makes sub
void CPU::sub(int result1, int result2 , string secondValueString, 
             string lastValueString)
{
    //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
        //find register name
        int size = findRegister( secondValueString );
        //convert the string to integer
        int lastNum = convertInteger( lastValueString );
        //sub register to number
        setRegister( size, -lastNum );
    }
    //if secondValueString and lastValueString are registers
    else if ( result1 == 1 && result2 == 1 )
    {
        //find register name
        int size1 = findRegister( secondValueString );
        //convert string to integer
        int size2 = findRegister( lastValueString );
        //sub register1 to register2
        setRegister( size1, -registerArray[size2]);
    }
}
// This function makes jump
int CPU::jmp( string secondValueString, string lastValueString, int jumpNum)
{
    //if jump have a variable and a constant
    if( jumpNum == 1 )
    {
        //find register name
        int size = findRegister( secondValueString );
        //convert string to integer
        int lastNum = convertInteger( lastValueString );
        //if value of register is equal 0
        if( registerArray[size] == 0 )
            return lastNum - 2; //go to line 
        else
            return PC; //continue from next line
    }
    //if jump has a value  
    else if( jumpNum == 2 )
    {
        //convert string to integer
        int num = convertInteger( secondValueString );
        return num - 2; // go to line
    }
}
// This function prints registers
void CPU::prn( string secondValueString )
{
    //control secondValueString what is register or number 
    int result = controlRegisterOrNumber( secondValueString );
    //if secondValueString is a register
    if( result == 1 )
    {
        //find register name and print on screen
        int num = findRegister( secondValueString );
            cout << "R " << num + 1 << " : " << registerArray[ num ];
    }
    //if secondValueString is a number
    else if( result == 2 )
    {
        //convert string to integer and print on screen
        int num = convertInteger( secondValueString );
        cout << num << endl;
    }
}
// This function controls string for register or number
const int CPU::controlRegisterOrNumber( const string str )
{	
    //if string is a register
    if( str.rfind("R") >= 0 && str.rfind("R") < str.size() ) 
        return 1;
    else 
        return 2;    
}
// This function register which is find 
const int CPU::findRegister( const string str )
{
	//if string is a register 1..
    if( str.compare("R1") == 0)
    	return 0;
    else if( str.compare("R2") == 0)
        return 1;
    else if( str.compare("R3") == 0)
        return 2;
    else if( str.compare("R4") == 0)
        return 3;
    else if( str.compare("R5") == 0)
        return 4;
    else
        return -1;
}
// This function erase space in string
const string CPU::eraseSpace( string str )
{
    //go till last value of the string
    for ( int i = 0 ; i < str.size() ; i++) 
    {
    	//if string have any of them(space,tab,newline), erase 
        if (str[i] == ' '  || str[i] == '\t' || str[i] == '\n' )
        {
            str.erase(i, 1);
            i--;
        }
    }
    return str;
}
// This function converts lower letters to upper letters
const string CPU::lowerUpper( string str )
{
    //go till last value of the string
    for(int i=0; i <str.size(); i++)
    {
        //if string has a lower case, change with upper case 
        if(str[i] >='a' && str[i]<='z')
            str[i]+='A'-'a';
    } 
   return str;
}
// This function is convert string to integer
const int CPU::convertInteger( string str )
{
    int result = 0;
    //sub all the value of the string from their ascıı value and convert integer
    for ( int i = 0 ; str[i] != '\0' ; ++i )
        result = result * 10 + str[i] - '0';
    return result;
}