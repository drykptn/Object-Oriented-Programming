/* 
 * File:   CPU.cpp
 * Author: derya
 * 
 * Created on 24 Ekim 2016 Pazartesi, 22:17
 */

#include "CPU.h"


CPU::CPU():PC(0){/*Empty constructor*/}
/* Takes an option from driver */
CPU::CPU( const int option ):incomingOption(option), PC(0){}
/* This function assigns to register*/
void CPU::setRegister( const int size, const int value ){
    registerArray[size] += value;
}
/* This function assign a null value to register*/
void CPU::setReg ( const int size , const int value ) {
    registerArray[size] = value;
}
/* This function assign value to PC */
void CPU::setPC( const int num ){
    PC = num;
}
/* This function return value of register array */
const int CPU::getRegister( const int size ){
    return registerArray[size];
}
/* This function return value of PC */
const int CPU::getPC(){
    return PC;
}
/* If instruction is 'HLT' , finish the program */
bool CPU::halted(){
    if( operation.compare("HLT") == 0 )
        return true;
    else
        return false;
}
void CPU::print()
{
    //print all the register on screen
    cout << "Register Values "<< endl;
    for (int i = 0; i < SIZE_OF_REGISTER ; ++i)
            cout << "[" << i << "] -> " << registerArray[i] << endl;
}
const int CPU::execute( string instruction, Memory& myMemoryObj ){
    string secondValueString, lastValueString;
    int i, j, currentLine;    
    int result1 = 0, result2 = 0, value = 0;
    
    if( instruction.rfind(";") >= 0 && instruction.rfind(";") < instruction.size() )
        instruction.erase( instruction.rfind(";") );
            //Change lower case to upper case
    instruction = lowerUpper( instruction );
        
    //if line has any of operation, continue,else fail
    if(  instruction.rfind("MOV") >= 0 && instruction.rfind("MOV") < instruction.size() ||
         instruction.rfind("ADD") >= 0 && instruction.rfind("ADD") < instruction.size() ||
         instruction.rfind("SUB") >= 0 && instruction.rfind("SUB") < instruction.size() ||
         instruction.rfind("JMP") >= 0 && instruction.rfind("JMP") < instruction.size() ||
         instruction.rfind("JPN") >= 0 && instruction.rfind("JPN") < instruction.size() ||    
         instruction.rfind("HLT") >= 0 && instruction.rfind("HLT") < instruction.size() ||
         instruction.rfind("PRN") >= 0 && instruction.rfind("PRN") < instruction.size() )
         {  
            // clean string from space
            instruction = eraseSpace( instruction );
            // parsing        
            for (int k = 0; k < 3 ; ++k)
                operation += instruction[k];
            //then erase operation from string
            instruction.erase( 0, 3 );
            //if instruction has "," , continue
            if( instruction.rfind(",") >= 0 && 
                instruction.rfind(",") <= instruction.size() )
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
            result1 = controlRegisterOrNumberOrAddress( secondValueString );
            result2 = controlRegisterOrNumberOrAddress( lastValueString );
            //if operation is "MOV",continue
            if( operation.compare("MOV") == 0 )
            {
                /*if user send a negative value to address, its send a error message
                on screen and finish the program*/
                myMemoryObj = move( result1 , result2, secondValueString, 
                                    lastValueString, myMemoryObj);
                int error = controlUnsignedAddress( myMemoryObj );
                if ( error == 1 )
                {
                    cerr << " You can't assign a negative number to memory" << endl;
                    return 0;
                }
            }
            //if operation is "ADD",get into
            else if( operation.compare("ADD") == 0 )
               myMemoryObj = add(result1 , result2, secondValueString, 
                                 lastValueString, myMemoryObj);
            //if operation is "SUB",get into
            else if( operation.compare("SUB") == 0 )
                myMemoryObj = sub( result1, result2 , secondValueString,
                                   lastValueString, myMemoryObj);
            //if operation is "JMP",get into
            else if( operation.compare("JMP") == 0 )
            {	
                //check control string what is register or number
                value = controlRegisterOrNumberOrAddress( secondValueString );
                //if string is a register
                if ( value == 1 )		       
                    currentLine = jmp( secondValueString, lastValueString, 1 );
                //if string is a number
                else if ( value == 2 )
                    currentLine = jmp( secondValueString, lastValueString, 2 );	
                // assign incoming current line to PC
                setPC( currentLine );
            }
            // If operation is "JPN", get into
            else if( operation.compare("JPN") == 0 )
            {
                if( result1 == 1 && result2 == 2 )
                    currentLine = jpn( secondValueString, lastValueString );
                setPC( currentLine );
            }
            // If operation is "PRN", get into
            else if( operation.compare("PRN") == 0 )
                prn( secondValueString, myMemoryObj );                 
            //if operation is "HLT",get into
            else if( operation.compare("HLT") == 0 )
            {
                //go to hlt function and finish the program
                print();
                myMemoryObj.printAll();
                return 0;
            }
            // if incoming option from user is equal 1, 
            // print all the register on screen
            if( incomingOption == 1 )
                print();
            // if incoming option from user is equal 2, 
            // print all the register and address on screen
            else if( incomingOption == 2 )
            {
                print();
                myMemoryObj.printAll();
            }
            // Empty all parse string,for reusability
            operation.erase(0);
            secondValueString.erase(0);
            lastValueString.erase(0);
            PC++;
        }
        else
        {
            //if user write a wrong type, fail and out of the loop
            cerr << "Syntax error!" << endl;
            // condition out of the loop
            return 0;
        }
}
// This function makes move
const Memory CPU::move( const int result1, const int result2 , 
                        string secondValueString,  string lastValueString, 
                        Memory& myMemoryObj ) 
{
   //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
        //find the register name 
        int size = findRegister( secondValueString );
        //convert the string to integer
        int lastNum = convertInteger( lastValueString );
        //be sure whether or not register is empty 
        setReg( size, 0 );
        //then copy th number to the register
        setRegister( size, lastNum );
    }
    //if secondValueString and lastValueString are registers 
    else if ( result1 == 1 && result2 == 1 )
    {
        //find the register name
        int size1 = findRegister( secondValueString );
        //find the register name
        int size2 = findRegister( lastValueString );
        //be sure whether or not register is empty 
        setReg( size2, 0 );
        //then copy 
        setRegister( size2 , registerArray[size1] ); 
    }
    //if secondValueString is a register and lastValueString is an address
    else if( result1 == 1 && result2 == 3 )
    {
        int size1 = findRegister( secondValueString );
        lastValueString.erase(0,1);
        int num = convertInteger( lastValueString );
        //be sure whether or not address is empty 
        myMemoryObj.setMemory( num , 0 );
        //then copy
        myMemoryObj.setMem(num, registerArray[size1]);
    }   
    //if secondValueString is an address  and lastValueString is a register
    else if( result1 == 3 && result2 == 1 )
    {
        // erase the "#", then convert the integer 
        secondValueString.erase(0,1);
        int num = convertInteger( secondValueString );
        int size = findRegister( lastValueString );
        //be sure whether or not register is empty 
        setReg( size, 0 );
        //then copy 
        setRegister( size, myMemoryObj.getMem( num ) );
    }			
   //if secondValueString is an address  and lastValueString is a constant
     else if( result1 == 3 && result2 == 2 )
    {
        // erase the "#", then convert the integer 
        secondValueString.erase(0,1);
        int num = convertInteger( secondValueString );
        int constant = convertInteger( lastValueString );
        //be sure whether or not register is empty 
        myMemoryObj.setMemory( num, 0 );
        //then copy
        myMemoryObj.setMem( num, constant );
    }
    return myMemoryObj;
}
// This function makes add
const Memory CPU::add( const int result1, const int result2 , const string 
                 secondValueString, string lastValueString, Memory& myMemoryObj )
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
        setRegister( size1, registerArray[size2] );

    }
    //if secondValueString is a register and lastValueString is an address
    else if( result1 == 1 && result2 == 3 )
    {
        //find the register name
        int size = findRegister( secondValueString );
        //erase the "#"
        lastValueString.erase(0,1);
        int num = convertInteger( lastValueString );
        setRegister( size, myMemoryObj.getMem(num));
    }	
    return myMemoryObj;
}
// This function makes sub
const Memory CPU::sub( const int result1, const int result2 , const string 
                 secondValueString, string lastValueString, Memory& myMemoryObj )
{ 
    //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
        //find register name
        int size = findRegister( secondValueString );
        //convert the string to integer
        int lastNum = convertInteger( lastValueString );
        //sub register to number
        setRegister(size, -lastNum);
 
    }
    //if secondValueString and lastValueString are registers
    else if ( result1 == 1 && result2 == 1 )
    {
        //find register name
        int size1 = findRegister( secondValueString );
        //convert string to integer
        int size2 = findRegister( lastValueString );
        //sub register1 to register2
        setRegister(size1 ,-registerArray[size2]);
    }
    //if secondValueString is a register and lastValueString is an address
    else if ( result1 == 1 && result2 == 3 )
    {
        //find the register name
        int size = findRegister( secondValueString );
        //erase the "#"
        lastValueString.erase(0,1);
        //find the number of address
        int num = convertInteger( lastValueString );
        //sub address to register
        setRegister(size, -myMemoryObj.getMem(num));

    }
    return myMemoryObj;
}
// This function makes jump
int CPU::jmp( const string secondValueString, const string lastValueString,
              const int jumpNum )
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
//This function if register is equal 0 or smaller, change line address, 
//else it continue
int CPU::jpn( const string secondValueString, const string lastValueString)
{
    int size = findRegister( secondValueString );
    int lastNum = convertInteger( lastValueString );
    //if register array is equal 0, jump, else continue
    if ( registerArray[ size ] == 0 || registerArray[ size ] < 0  )
        return lastNum - 2 ;
    else
        return PC; 
}
// This function prints registers
void CPU::prn( string secondValueString, Memory& myMemoryObj ) 
{
    //control secondValueString what is register or number 
    int result = controlRegisterOrNumberOrAddress( secondValueString );
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
    // if secondValueString is an address
    else if( result == 3 )
    {
        // erase the "#" and print number of address
        secondValueString.erase(0,1);
        int num = convertInteger( secondValueString );
        cout << myMemoryObj.getMem(num) << endl;
    }
}
// This function controls string for register or number
const int CPU::controlUnsignedAddress( Memory& myMemoryObj )
{
    //if value of memory is negative
    for (int i = 0; i < SIZE_OF_ADDRESS ;  i++ )
    {
        if( myMemoryObj.getMem(i) > 10000 )
            return 1;
        else
            return 2; 
    }
}
// This function controls string for register or number
int CPU::controlRegisterOrNumberOrAddress( string str )
{
    //if string is a register
    if( str.rfind("R") >= 0 && str.find("R") < str.size() ) 
        return 1;
    //if string is an address
    else if( str.rfind("#") >= 0 && str.rfind("#") < str.size() )
    	return 3;
    // if string is a constant
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
        cerr << "Register was not find" << endl;
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
            str[i] += 'A' - 'a';
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