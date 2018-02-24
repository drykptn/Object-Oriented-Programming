/*
* You will continue developing your CPU in this homework. You will have now memory instructions
for your CPU. The memory addreses and constrnts should be kept different, so we represent
memory addresses with a # sign as a prefix. For example 100 is a constant but #100 is an address.
The instruction in HW1 are still valid. Your new instructions are
Move instructions
MOV reg, address
MOV address, reg
MOV address, constant
For example MOV R1, #45 copies the value of register 1 to memory location 45
Addition and Subtraction insructions
ADD reg, address
SUB reg, address
For example, ADD R1, #45 adds the value of memory location 45 to register 1
Print instructions
PRN address
For example, PRN #56 will print the value of the memory loacation 56 to the screen, after each print
a new line should be inserted.
Jump instruction
JPN reg, lineAdress
JPN R1, 32 jumps to line 32 of the program if the value of R1 is zero or smaller.
New example for clarification
SUB R1, R2 subtracts the value of register 2 from register 1 and puts the result into register 1
Modified instructions
HLT
halts the program and prints on the screen the contents of all registers as well as the the memory.Your program will run using the same command line parameters as HW1. However, we have a new
option
The format for the command line parameters is as follows
yourProg filename option
yourProg is the name of your executable file, file name is the text file that contains your simple CPU
instructions, option a number and the defines the how your program runs as follows
• if option is 0, your program will run and finish by executing each instruction
• if option is 1, your program will execute each instruction after displaying the instruction first.
It also will print the contents of all the registers.
• If option is 2, your program will execute each instruction just like the option 1. This option
will also print the contents of the memory after each intruction execution.
Write a CPU program that sort 10 integers from smallest to largest. The integers are 30, 23, 4, 56,
34, 56, 89, 32, 45, 25. Ypu program should write these integers to the memory using MOV
instructions first. You will include your program with your submission.
 */

/* 
 *            Homework 2 
 *  Author: 141044025-Derya KAPTAN
 */
#include <iostream>
#include <fstream>
#include <string>
#define SIZE_ARRAY 5
#define SIZE_MEMORY 50

using namespace std;

//This function erase space in a string
string eraseSpace( string str );
// This function converts lower letters to upper letters
string lowerUpper( string str);
// This function find register name
int findRegister( string str );
//This function convert a string to integer
int convertInteger( string str );
//This function controls strings to register or number
int controlRegisterOrNumberOrAddress( string str );
//This function controls values of memory
int controlUnsignedAddress( unsigned int address[] );
//This function makes addition
int add( int a , int operation );
//This function copies the value each other
int move( int result1, int result2 , string secondValueString, string  
	      lastValueString, int registerArray[], unsigned int address[]);
//This function makes addition
int add( int result1, int result2 , string secondValueString, string
         lastValueString, int registerArray[], unsigned int address[]);
//This function makes subtraction
int sub(int result1, int result2 , string secondValueString, string
        lastValueString, int registerArray[], unsigned int address[]);
//This function control number and when needed its change line
int jmp( string secondValueString, string lastValueString, int registerArray[],
         int m, int jumpNum );
//This function control register  and when needed its change line
int jpn(string secondValueString, string lastValueString, int registerArray[],
        int m );
//This function prints register or constant
void print( int registerArray[], string str, unsigned  int address[], int m );
//This function print all the register on screen and finish the program
void hlt( int registerArray[], unsigned int address[], int num );


int main(int argc, char** argv) 
{
    fstream input;
    string line; 
    string operation; //operation string( mov, add, ..)
    string lastValueString; //The second arguman in a line(if MOV,R1,10, "R1")
    string secondValueString;//The third arguman in a line(if MOV,R1,10, "10")
    string  fileStr[200]; //it contains all the lines in file
    int result1 = 0, result2 = 0;
    int i = 0, j = 0;
    int registerArray[ SIZE_ARRAY ] = {0}; //register values array
    unsigned int address[ SIZE_MEMORY ] = {0};  //address of memory array
    
    if ( argc == 3 )
    {
        input.open( argv[1] );
        if( input.is_open() )
        {
            int count = 0; 
            //to find number of line in file
            while( !input.eof() )
            {
                getline( input, line ); // read a line by line from file   		
                fileStr[count] = line; // and put the line a string array
                count++;
            }
            int m = 0;	// read till count-1 
            while( m != count - 1)
            {
                line = fileStr[m];
                //if line has a ";", erase as from ";"
                if( line.rfind(";") >= 0 && line.rfind(";") < line.size() )
                    line.erase( line.rfind(";") );
                //Change lower case to upper case
                line = lowerUpper( line );

                //if line has any of operation, continue,else fail
                if( line.rfind("MOV") >= 0 && line.rfind("MOV") < line.size() ||
                    line.rfind("ADD") >= 0 && line.rfind("ADD") < line.size() ||
                    line.rfind("SUB") >= 0 && line.rfind("SUB") < line.size() ||
                    line.rfind("JMP") >= 0 && line.rfind("JMP") < line.size() ||
                    line.rfind("JPN") >= 0 && line.rfind("JPN") < line.size() ||    
                    line.rfind("HLT") >= 0 && line.rfind("HLT") < line.size() ||
                    line.rfind("PRN") >= 0 && line.rfind("PRN") < line.size() )
                    {
                        // clean string from space
                        line = eraseSpace( line );
                        //takes operation name from line string
                        for (int k = 0; k < 3 ; ++k)
                            operation += line[k];
                        //then erase operation from string
                        line.erase( 0, 3 );
                        //if line has "," , continue
                        if( line.rfind(",") >= 0 && line.rfind(",") <= line.size() )
                        {
                            //read till ",", and put a another string
                            for ( i = 0; line[i] != ',' ; ++i)
                                secondValueString += line[i];
                            //read rest of them till size of line
                            for ( j = i + 1 ; j < line.size(); ++j)
                                lastValueString += line[j]; 		
                        }
                        // for JMP constant 
                        else
                        {
                            //read till size of line and put a another string
                            for ( i = 0; i < line.size() ; ++i)
                                secondValueString += line[i];
                        }
                        //check control string what is register or number
                        //and if it is a register, return 1, else return 2
                        result1 = controlRegisterOrNumberOrAddress( secondValueString );
                        result2 = controlRegisterOrNumberOrAddress( lastValueString);
                        //if operation is "MOV",continue
                        if( operation.compare("MOV") == 0 )
                        {
                            move( result1 , result2, secondValueString, lastValueString, registerArray, address);
                            int error = controlUnsignedAddress( address );
                            if ( error == 1 )
                            {
                                cerr << " You can't assign a negative number to memory" << endl;
                                m = count - 1;
	                        }
	                    }
                         //if operation is "ADD",continue
                        else if( operation.compare("ADD") == 0 )
                            add(result1 , result2, secondValueString, lastValueString, registerArray, address);
                        //if operation is "SUB",continue
                        else if( operation.compare("SUB") == 0 )
                            sub( result1, result2 , secondValueString,lastValueString,registerArray, address);
                        //if operation is "JMP",continue
                        else if( operation.compare("JMP") == 0 )
                        {	
                            //if string is a register
                            if ( result1  == 1 )		       
                                m = jmp( secondValueString, lastValueString, registerArray, m , 1 );
                            //if string is a number
                            else if ( result1  == 2 )
                            	m = jmp( secondValueString, lastValueString, registerArray, m , 2 );	
                        }
                        else if( operation.compare("JPN") == 0 )
                        {
                            if( result1 == 1 && result2 == 2 )
                                m = jpn( secondValueString, lastValueString, registerArray,  m );
                        }
                        //if operation is "PRN",continue
                        else if( operation.compare("PRN") == 0 )
                                print( registerArray, secondValueString, address, m );                 
                            //if operation is "HLT",continue
                        else if( operation.compare("HLT") == 0 )
                        {
                            //go to hlt function and finish the program
                            hlt( registerArray, address, 1 );
                            hlt( registerArray, address, 2 );
                            return 0;
                        }
                        else
                            cerr << "Error! Unexpected operation name.." << endl;
                        //if argument is equal 1, print registers on screen
                        if( *argv[2] == '1' )
                            hlt( registerArray, address, 1 );
                        //if argument is equal 2, print registers and addresses on screen
                        else if( *argv[2] == '2' )
                        {
                            hlt( registerArray, address, 1 ); 
                            hlt( registerArray, address, 2 ); 
                        }
                         //erase all the string for reusability
                        operation.erase(0);
                        secondValueString.erase(0);
                        lastValueString.erase(0);			    
                        m++;
                         
		            }
		            else
		            {
		                //if user write a wrong type, fail and out of the loop
		                cerr << "Syntax error!" << endl;
		                m = count - 1; // condition out of the loop
		        	}
        	}
        }	
        else //file could not be opened
            cerr << "File could not be opened." << endl;
        input.close();
    }
    else
        cerr << "Error! You can't write more than 3 argument." << endl;
    return 0;
}
// This function makes move
int move( int result1, int result2 , string secondValueString, string
          lastValueString, int registerArray[], unsigned int address[] ) 
{	
    //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
	    //find the register name 
	    int size = findRegister( secondValueString );
	    //convert the string to integer
	    int lastNum = convertInteger( lastValueString );
	    //then copy th number to the register
	    registerArray[size] = 0;
	    registerArray[size] += lastNum;
	    return *registerArray;
    }
    //if secondValueString and lastValueString are registers 
    else if ( result1 == 1 && result2 == 1 )
    {
        //find the register name
        int size1 = findRegister( secondValueString );
        //find the register name
        int size2 = findRegister( lastValueString );
        //be sure whether or not register is empty 
        registerArray[size2] = 0;
        //then copy 
        registerArray[size2] += registerArray[size1]; 
        return *registerArray;
    }
    //if secondValueString is a register and lastValueString is an address
    else if( result1 == 1 && result2 == 3 )
    {
        int size1 = findRegister( secondValueString );
        lastValueString.erase(0,1);
        int num = convertInteger( lastValueString );
        address[num] = 0;
        address[num] += registerArray[size1];
        return *registerArray;
}
    //if secondValueString is an address  and lastValueString is a register
    else if( result1 == 3 && result2 == 1 )
    {
        secondValueString.erase(0,1);
        int num = convertInteger( secondValueString );
        int size = findRegister( lastValueString );
        registerArray[size] = 0;
        registerArray[size] += address[num];
        return *registerArray;
    }			
   //if secondValueString is an address  and lastValueString is a constant
     else if( result1 == 3 && result2 == 2 )
    {
        secondValueString.erase(0,1);
        int num = convertInteger( secondValueString );
        int constant = convertInteger( lastValueString );
        address[num] += constant;
        return *address;
    }
}
// This function makes add
int add(int result1, int result2 , string secondValueString, string
        lastValueString, int registerArray[], unsigned int address[] )
{
    //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
        //find the register name 
        int size = findRegister( secondValueString );
        //convert the string to integer
        int lastNum = convertInteger( lastValueString );
        // add number to register
        registerArray[size] += lastNum;
        return *registerArray;
	}
    //if secondValueString and lastValueString are registers 
    else if ( result1 == 1 && result2 == 1 )
    {
        //find the register name
        int size1 = findRegister( secondValueString );
        //find the register name
        int size2 = findRegister( lastValueString );
        //add register2 to register1
        registerArray[size1] += registerArray[size2];
        return *registerArray;
    }
    //if secondValueString is a register and lastValueString is an address
    else if( result1 == 1 && result2 == 3 )
    {
        //find the register name
        int size = findRegister( secondValueString );
        //erase the "#"
        lastValueString.erase(0,1);
        int num = convertInteger( lastValueString );
        registerArray[size] += address[num];
        return *registerArray;
    }	
}
// This function makes sub
int sub(int result1, int result2 , string secondValueString, string
        lastValueString, int registerArray[], unsigned int address[] )
{ 
    //if secondValueString is a register and lastValueString is a number
    if( result1 == 1 && result2 == 2 )
    {
        //find register name
        int size = findRegister( secondValueString );
        //convert the string to integer
        int lastNum = convertInteger( lastValueString );
        //sub register to number
        registerArray[size] -= lastNum;
        return *registerArray;
	}
    //if secondValueString and lastValueString are registers
    else if ( result1 == 1 && result2 == 1 )
    {
        //find register name
        int size1 = findRegister( secondValueString );
        //convert string to integer
        int size2 = findRegister( lastValueString );
        //sub register1 to register2
        registerArray[size1] -= registerArray[size2];
        return *registerArray;
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
	    registerArray[size] -= address[num];
	    return *registerArray;
    }
}
// This function makes jump
int jmp( string secondValueString, string lastValueString, int registerArray[],
         int m, int jumpNum )
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
            return m; //continue from next line
	}
    //if jump has a value  
    else if( jumpNum == 2 )
    {
        //convert string to integer
        int num = convertInteger( secondValueString );
        return num - 2; // go to line
	}
}
//This function if register is equal 0 or smaller, change line address, else it continue
int jpn(string secondValueString, string lastValueString, int registerArray[],
        int m )
{
    int size = findRegister( secondValueString );
    int lastNum = convertInteger( lastValueString );
    if ( registerArray[ size ] == 0 || registerArray[ size ] < 0  )
        return lastNum - 2 ;
    else
        return m; 
}
// This function prints registers
void print( int registerArray[] , string secondValueString, unsigned int
            address[], int m )
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
        cout << address[num] << endl;
	}
}
// This function finish the program and print value of registers and address on screen
void hlt( int registerArray[], unsigned int address[], int num )
{
    // for value of register
    if( num == 1 )
    {
        for (int i = 0; i < SIZE_ARRAY ; ++i)
            cout << "R" << i+1 << " : " << registerArray[i] << endl;
    }
    // for value of address
    else if( num == 2 )
    {
        for (int i = 0; i < SIZE_MEMORY  ;  ++i)
        {
            cout << "#" << i << " : " << address[i] << " | ";
            if( i == 9 || i == 19 || i == 29 || i == 39 )
                cout << endl;
        }
        cout << endl;
     }
}
//This function controls values of memory
int controlUnsignedAddress( unsigned int address[] )
{
	//if value of memory is negative
    for (int i = 0; i < SIZE_MEMORY ;  i++ )
    {
        if( address[i] > 10000 )
            return 1;
        else
            return 2; 
    }
}
// This function controls string for register or number
int controlRegisterOrNumberOrAddress( string str )
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
int findRegister( string str )
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
        cerr << "Error! You should write 3 arguments" << endl;
}
// This function erase space in string
string eraseSpace( string str )
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
string lowerUpper( string str )
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
int convertInteger( string str )
{
    int result = 0;
    //sub all the value of the string from their ascıı value and convert integer
    for ( int i = 0 ; str[i] != '\0' ; ++i )
        result = result * 10 + str[i] - '0';
    return result;
}

