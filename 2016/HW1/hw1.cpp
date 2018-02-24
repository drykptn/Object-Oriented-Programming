/*
You will write a C++ program that will simulate a very simple CPU. Your CPU has only 5 registers
(R1, R2, R3, R4, R5) and no other memory. Your CPU has a small set of instructions as decribed
below.
Move instructions
MOV reg, reg
MOV reg, constant
For example MOV R1, R2 copies the value of register 1 to register 2
and MOV R1, 100 puts the value of 100 to register 1
Addition and Subtraction insructions
ADD reg, reg
ADD reg, constant
SUB reg, reg
SUB reg, constant
For example, ADD R1, R2 adds the value of register 2 to register 1
and ADD R1, 100 adds the value of 100 to register 1
Jump instruction
JMP reg, lineAdress
JMP lineAddress
For example, JMP R1, 32 jumps to line 32 of the program if the value of R1 is zero. JMP 23 jumps to
line 23 directly.
Print instructions
PRN reg
PRN constant
For example, PRN R3 will print the value of register 3 to the screen, after each print a new line
should be inserted.
Other instructions
HLT
halts the program and prints on the screen the contents of all registers.Following is a program file that prints numers from 10 down to 0 to the screen

As seen above, you may have comments after each instruction after the ; sign. Each line of your
program file shoud contain a single instruction, so the line numbers will correspond to the instruction
numbers.
Your program will run using the command line parameters. The format for the command line
parameters is as follows
yourProg filename option
yourProg is the name of your executable file, file name is the text file that contains your simple CPU
instructions, option a number and the defines the how your program runs as follows
• if option is 0, your program will run and finish by executing each instructions
• if option is 1, your program will execute each instruction after displaying the instruction first.
It also will print the contents of all the registers such as
MOV R1, 10 – R1=10, R2=0, R3=0, R4=0, R5=0
*/
/*
 * The program is a very simple CPU. 
 */

/* 
 * Author: 141044025-Derya KAPTAN
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#define SIZE_ARRAY 5

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
int controlRegisterOrNumber( string str );
//This function makes addition
int add( int a , int operation );
//This function copies the value each other
int move( int result1, int result2 , string secondValueString, string lastValueString, int registerArray[]);
//This function makes addition
int add(int result1, int result2 , string secondValueString, string lastValueString, int registerArray[]);
//This function makes subtraction
int sub(int result1, int result2 , string secondValueString, string lastValueString, int registerArray[]);
//This function control number and when needed its change line
int jmp( string secondValueString, string lastValueString , string *fileStr, int registerArray[], int m, int jumpNum);
//This function prints register or constant
void print( int registerArray[], string str );
//This function print all the register on screen and finish the program
void hlt( int registerArray[] );


int main(int argc, char** argv) 
{
	fstream input;
    string line; 
    string operation; //operation string( mov, add, ..)
    string lastValueString; //The second arguman in a line(if MOV,R1,10, "R1")
    string secondValueString;//The third arguman in a line(if MOV,R1,10, "10")
    string  fileStr[200]; //it contains all the lines in file
    int secondNum = 0 , lastNum = 0;
    int result1 = 0, result2 = 0;
    int x = 0, y = 0 ;
    int i = 0, j = 0, num = 0, value = 0;
    int registerArray[ SIZE_ARRAY ] = {0}; //register values array
    
   	input.open(argv[1]);
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
				line.rfind("HLT") >= 0 && line.rfind("HLT") < line.size() ||
				line.rfind("PRN") >= 0 && line.rfind("PRN") < line.size() )
			{
				// clean string from space
			    line = eraseSpace( line );
			    cout << line << endl;
			 	//takes operation name from line string
				for (int k = 0; k < 3 ; ++k)
				{
					operation += line[k];
				}
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
				}// for JMP constant 
				else
				{
					//read till size of line and put a another string
					for ( i = 0; i < line.size() ; ++i)
						secondValueString += line[i];
				}
				//check control string what is register or number
 				//and if it is a register, return 1, else return 2
 				result1 = controlRegisterOrNumber( secondValueString );
				result2 = controlRegisterOrNumber( lastValueString );
				//if operation is "MOV",continue
				if( operation.compare("MOV") == 0 )
					move( result1 , result2, secondValueString, lastValueString, registerArray);
				//if operation is "ADD",continue
				else if( operation.compare("ADD") == 0 )
		        	add(result1 , result2, secondValueString, lastValueString, registerArray);
		        //if operation is "SUB",continue
		        else if( operation.compare("SUB") == 0 )
		        	sub( result1, result2 , secondValueString,lastValueString,registerArray);
		        //if operation is "JMP",continue
				else if( operation.compare("JMP") == 0 )
		        {	
		        	//check control string what is register or number
		        	value = controlRegisterOrNumber( secondValueString );
		        	//if string is a register
					if ( value == 1 )		       
						m = jmp( secondValueString, lastValueString, fileStr,registerArray, m , 1 );
		       		//if string is a number
		       		else if ( value == 2 )
		       			m = jmp( secondValueString, lastValueString, fileStr,registerArray, m , 2 );	
		       	}
		       	//if operation is "PRN",continue
		       	else if( operation.compare("PRN") == 0 )
			       	print( registerArray, secondValueString);                 
			    //if operation is "HLT",continue
		        else if( operation.compare("HLT") == 0 )
		        {
		        	//go to hlt function and finish the program
		        	hlt( registerArray );
		        	return 0;
		        }
		        else
			        cerr << "Error! Unexpected operation name.." << endl;
			    //for argument string
			    string option;
			    //throw argument to string
			    option += argv[2];
			    //convert string to integer
			    int optionNum = convertInteger( option ); 
			    //if argument is a 1 
			    if( optionNum == 1 )
			    	hlt( registerArray );
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
    return 0;
}
// This function makes move
int move( int result1, int result2 , string secondValueString, string lastValueString, int registerArray[]) 
{	

	//if secondValueString is a register and lastValueString is a number
	if( result1 == 1 && result2 == 2 )
	{
		//find the register name 
		int size = findRegister( secondValueString );
		//convert the string to integer
		int lastNum = convertInteger( lastValueString );
		//then copy th number to the register
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
	return -1;
}
// This function makes add
int add(int result1, int result2 , string secondValueString, string lastValueString, int registerArray[])
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
}
// This function makes sub
int sub(int result1, int result2 , string secondValueString, string lastValueString, int registerArray[])
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
}
// This function makes jump
int jmp( string secondValueString, string lastValueString , string fileStr[], int registerArray[], int m, int jumpNum)
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
// This function prints registers
void print( int registerArray[] , string secondValueString )
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
void hlt( int registerArray[] )
{
	//print all the register on screen
	for (int i = 0; i < SIZE_ARRAY ; ++i)
		cout << "R" << i+1 << " : " << registerArray[i] << endl;
}
// This function controls string for register or number
int controlRegisterOrNumber( string str )
{	
	//if string is a register
    if( str.rfind("R") >= 0 && str.find("R") < str.size() ) 
        return 1;
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
        return -1;
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

