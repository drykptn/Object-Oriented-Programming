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
