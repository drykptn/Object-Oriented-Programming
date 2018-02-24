/*
In this homework, you will re-write your game of Connect Four program in C++ using dynamic
memory techniques. You will not use any vectors or constant sized arrays.
Your main class for this homework will be named ConnectFour. This class will have a private
inner class named Cell to represent a Connect Four cell. The class Cell will hold the position of
the cell (A, B, C, etc) and the row number (1, 2, 3, etc). This class will also include all necessary
setters/getters, constructors etc. Remember a cell can be empty, user (user1, user2) or computer. You
will overload the following operators for the class cell.
• Operator== to compare two cells
• Pre and post increment/decrement operators for cell. The ++ operator changes the cell state
from empty to user1, from user1 to user2, from user2 to computer, from computer back to
empty.
• Stream insertion and extraction operators for cell.
Next, write a class named ConnectFour to represent and play the game. The class
ConnectFour will hold a Cell ** gameBoard data member to represent the game board as
a two dimensional dynamic array.
The class ConnectFour will also have the following features and functions
• There is no limit for the board. Your game will resize according to the parameter for the
constructor.
• There should be at least 3 constructors.
o The no parameter constructor creates a 5x5 game
o Another contructor takes number of rows and columns as parameters
o Another constructor takes a text file as a parameter. This text file will contain the
board shape marked with * characters. For example, the following is a board
configuration: it has 7 rows and 17 columns. Some of the columns are shorter than the
others.

The class will have functions to read and write from files. You will decide on the file format.
The class will have functions to print the current configuration of the board to the screen.
•
The class will have two functions named play that plays the game for a single time step. First
function does not take a parameter and it plays the computer. The second function takes a cell
position and it plays the user.
The class should have a function that returns if the game ended.
The class should have a function named playGame. This function plays the game by asking
the user the board file name first then asks the user to play and the computer plays, etc.
• The class will overload operator== and operator !=
• Any other functions (public or private) needed.
Write your main function to test both classes. Make at least 5 objects of class ConnectFour and
play the games at the same time.
You will use all the object oriented techniques that we learned in the class including const,
static, inline keywords.
*/
//
// Created by derya on 01.11.2017.
//

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

class ConnectFour{
public:
    // constructors
    ConnectFour();                    // default constructor
    // user direk filename ile contructor cagirirsa oyun load edilir ve kaldigi yerden devam eder.
    ConnectFour(string filename);
    ConnectFour(char mode);
    ConnectFour(int w, int h);
    ~ConnectFour();
    ConnectFour(const ConnectFour& other);

    // getter(inline) functions
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    int getPlayer() const { return player; }
    int getTwoLetter() const { return twoLetter; }
    char getChoice() const { return choice; }
    char getMoveLetter() const { return moveLetter; }
    char getGameMode() const { return gameMode; }
    bool getGame() const { return game; }

    static int getLivingCell();


    /* for hw3 */
    /*-----------------------------------------*/
    void takeBoardSize();
    void initializeBoard();
    /*-----------------------------------------*/

    // overload play functions
    int play();
    void play(int& lineLength);

    void selectGame();
    void printBoard() const;
    int saveGame(const string& fileName)const;
    int takeMove(int& error, string& filename, int& saveOrLoad, int& lineLength);
    int playGame();
    int loadGame(string fileName, int& loadPlayer, int lineLength);
    void readFileBoard();
    void selectGameMode();
    void initializeBoardFromFile(string filename);
    void startGame();


    // compare overload function
    bool operator >=( const ConnectFour& other) const;
    bool operator ==(const ConnectFour& other) const;
    bool operator !=(const ConnectFour& other) const;
    ConnectFour& operator=(const ConnectFour& other);

private:
    int width;
    int height;
    int player;
    int count;
    int twoLetter;
    char choice;
    char gameMode;
    char moveLetter;
    bool game;
    static int livingCell;

    // setter functions
    void setWidth(int num);
    void setHeight(int num);
    void setGameMode(char mode);
    void setPlayer(int num);


    static void setLivingCell();
    void firstComputerMove();
    void checkGameMode();
    int blockX();
    void checkMove(const int& error, const int& location, bool& control);
    int findLocation(int lineLength);
    bool checkFullBoard(int& lineLenght);
    bool win(int player, bool& game);
    bool winControl(char user);
    int testBoardSize(int num);
    int findMaxLineInFile(string& filename);
    int findSizeOfFile(string& filename);
    void arrAllocation();
    void boardAssignEmptySpace();

    int inputControl(int &saveOrLoad, string &line, string& filename);
    bool win();


    // inner class
    class Cell{
    public:
        Cell(){}        // default constructor

        // setter functions
        void setPosition(char letter);

        // overload functions
        bool operator==(const Cell& other)const ;
        Cell operator++() ;                    // prefix
        Cell operator --() ;                   // prefix
        Cell operator ++(int ignoreMe) ;       // postfix
        Cell operator --(int ignoreMe) ;       // postfix
        friend ostream& operator <<(ostream& outputStream, Cell const& board);          // cout overload
        friend istream& operator >>(istream& inputStream, Cell& board);                 // cin overload

        // getter functions
        char getPosition() const{ return  position; }

    private:
        int row;        // 1,2,3..
        char position;   // A,B,C..
    };
    Cell** gameBoard;

    // stream overload for inner class
    friend ostream& operator <<(ostream& outputStream, ConnectFour::Cell const& board);          // cout overload
    friend istream& operator >>(istream& inputStream, ConnectFour::Cell& board);                 // cin overload

};
#endif //CONNECTFOUR_H
