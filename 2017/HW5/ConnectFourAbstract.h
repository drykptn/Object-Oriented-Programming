//
// Created by derya on 22.11.2017.
//

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include "Cell.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

namespace Zeytin {

    class ConnectFourAbstract {
    public:
        ConnectFourAbstract();

        ConnectFourAbstract(char mode);

        ConnectFourAbstract(int w, int h);

        // big three
        ConnectFourAbstract(const ConnectFourAbstract &other);
        ConnectFourAbstract& operator=(const ConnectFourAbstract &other);
        ~ConnectFourAbstract();

        // getter functions
        int currentPlayer() const { return _player; }

        int getWidth() const { return _width; }

        int getHeight() const { return _height; }

        char getChoice() const { return _choice; }

        char getMoveLetter() const { return _moveLetter; }

        int saveGame(const string &fileName) const;

        void printBoard() const;

        virtual int playGame() = 0;

        bool win();

    protected:
        int _width;
        int _height;
        int _player;
        int _count;
        char _choice;
        char _moveLetter;
        bool _game;
        Cell **gameBoard;
        int *undo;    // hamleleri tutan int array i

        virtual int startGame() = 0;

        virtual int play() = 0;

        virtual int blockX() = 0;

        virtual bool winControl(char user) = 0;

        virtual int loadGame(string fileName, int &loadPlayer, int lineLength) = 0;

        virtual void play(int &lineLength) = 0;

        void setWidth(int num);

        void setHeight(int num);

        void arrAllocation();

        void firstComputerMove();

        int takeMove(int &error, string &filename, int &saveOrLoad, int &lineLength);

        int findLocation(int lineLength);

        void checkMove(const int &error, const int &location, bool &control);

        void initializeBoard();

        void takeBoardSize();

        int testBoardSize(int num);

        bool checkFullBoard(int &lineLength);

        void selectGame();

        int appendUndoArr(int x);

        int findLastLocation();
    };
}

#endif //CONNECTFOURABSTRACT_H
