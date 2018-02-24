//
// Created by derya on 22.11.2017.
//

#include "ConnectFourPlusUndo.h"

namespace Zeytin {

    int ConnectFourPlusUndo::playGame() {
        takeBoardSize();
        arrAllocation();
        initializeBoard();
        selectGame();
        printBoard();
        startGame();
    }

    void ConnectFourPlusUndo::undoMove() {
        int size = 0, i = 0;
        // hamle sayisi hesaplanir. undo array size ı
        while (undo[i] != -1) {
            ++size;
            ++i;
        }
        // hamleyi geri alır
        for (int j = 0; j < getHeight(); ++j) {
            if (gameBoard[j][undo[size - 1]].getPosition() != '.') {
                gameBoard[j][undo[size - 1]].setPosition('.');
                j = getHeight() + 1;
            }
        }
    }

    void ConnectFourPlusUndo::play(int &lineLength) {
        int error = 0, saveOrLoadOrUndo = 0, loadPlayer;
        string filename;
        bool control, loop = true;

        loadPlayer = _player;

        while (loop) {
            control = true;
            saveOrLoadOrUndo = 0;
            // hamleyi al
            if (takeMove(error, filename, saveOrLoadOrUndo, lineLength) == -1)
                takeMove(error, filename, saveOrLoadOrUndo, lineLength);

            if (saveOrLoadOrUndo == 1) {
                if (saveGame(filename) == -1)
                    cerr << "The game could not saved" << endl;
                else
                    cout << "The game saved." << endl;
            } else if (saveOrLoadOrUndo == 2) {
                if (loadGame(filename, loadPlayer, lineLength) == -1)
                    cout << "The game could not load" << endl;
                _player = loadPlayer;
            } else if (saveOrLoadOrUndo == 3) {
                undoMove();

                // user degistirerek oyuna devam eder
                if (_player == 1)
                    _player = 2;
                loadPlayer = 2;
                _player = 1;
                loadPlayer = 1;
            } else {
                // konumu bul
                int location = findLocation(lineLength);

                // hamleyi check et
                checkMove(error, location, control);
                if (location == -1) {
                    loop = false;
                    control = false;
                }

                if (control && gameBoard[location][getMoveLetter() - 97].getPosition() ==
                               '.')   // dogruysa donguden cik ve board u print et
                {
                    loop = false;
                    if (_player == 1) {         // user1
                        gameBoard[location][getMoveLetter() - 97].setPosition('X');
                        appendUndoArr(getMoveLetter() - 97);
                    } else if (_player == 2) {        // user2
                        gameBoard[location][getMoveLetter() - 97].setPosition('O');
                        appendUndoArr(getMoveLetter() - 97);
                    }
                    cout << "User -> " << _player << endl << endl;
                }
            }
            printBoard();
        }
    }
}