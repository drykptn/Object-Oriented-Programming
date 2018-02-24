//
// Created by derya on 22.11.2017.
//

#include "ConnectFourDiag.h"

namespace Zeytin {

    int ConnectFourDiag::playGame() {
        takeBoardSize();
        arrAllocation();
        initializeBoard();
        selectGame();
        printBoard();
        startGame();
    }


    bool ConnectFourDiag::winControl(char user) {
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                // sag capraz user1 - user2
                if (gameBoard[i][j].getPosition() == user) {
                    if (i - 1 >= 0 && j + 1 <= getHeight() && gameBoard[i - 1][j + 1].getPosition() == user) {
                        if (i - 2 >= 0 && j + 2 <= getHeight() && gameBoard[i - 2][j + 2].getPosition() == user) {
                            if (i - 1 >= 0 && j + 3 <= getHeight() && gameBoard[i - 3][j + 3].getPosition() == user) {
                                cout << "-------------------------------------------------------------" << endl;
                                cout << endl << "FINAL BOARD !! " << endl;
                                for (int k = 0; k < 4; ++k)
                                    gameBoard[i - k][j + k].setPosition(static_cast<char>(tolower(gameBoard[i - k][j +
                                                                                                                   k].getPosition())));   // kazanirsa harfleri kucuge cevirir.
                                printBoard();
                                return true;
                            }
                        }
                    }
                }
                // sol capraz user1 - user2
                if (gameBoard[i][j].getPosition() == user) {
                    if (i - 1 >= 0 && j + 1 >= 0 && gameBoard[i - 1][j - 1].getPosition() == user) {
                        if (i - 2 >= 0 && j - 2 >= 0 && gameBoard[i - 2][j - 2].getPosition() == user) {
                            if (i - 3 >= 0 && j - 3 >= 0 && gameBoard[i - 3][j - 3].getPosition() == user) {
                                cout << endl << "FINAL BOARD !! " << endl;
                                cout << "-------------------------------------------------------------" << endl;
                                for (int k = 0; k < 4; ++k)
                                    gameBoard[i - k][j - k].setPosition(static_cast<char>(tolower(gameBoard[i - k][j -
                                                                                                                   k].getPosition())));   // kazanirsa harfleri kucuge cevirir.
                                printBoard();
                                return true;
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    int ConnectFourDiag::blockX() {
        int result = 0;
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                if (gameBoard[i][j].getPosition() == 'X') {
                    /*------------------------------------------------------------------------------*/
                    // sag capraz icin
                    if (gameBoard[i - 1][j + 1].getPosition() == 'X' &&
                        gameBoard[i - 2][j + 2].getPosition() == '.') {
                        if (gameBoard[i - 1][j + 2].getPosition() != '.') {
                            gameBoard[i - 2][j + 2].setPosition('O');
                            return 1;
                        } else if (gameBoard[i + 1][j - 1].getPosition() == '.' &&
                                   gameBoard[i + 2][j - 1].getPosition() != '.') {
                            gameBoard[i + 1][j - 1].setPosition('O');
                            return 1;
                        }
                    }
                        /*------------------------------------------------------------------------------*/
                        // sol capraz icin
                    else if (gameBoard[i - 1][j - 1].getPosition() == 'X' &&
                             gameBoard[i - 2][j - 2].getPosition() == '.') {
                        if (gameBoard[i - 1][j - 2].getPosition() != '.') {
                            gameBoard[i - 2][j - 2].setPosition('O');
                            return 1;
                        } else if (gameBoard[i + 1][j + 1].getPosition() == '.' &&
                                   gameBoard[i + 2][j + 1].getPosition() != '.') {
                            gameBoard[i + 1][j + 1].setPosition('O');
                            return 1;
                        }
                    }
                }
            }
        }
        return result;
    }

    int ConnectFourDiag::play() {
        int result = 0;
        // board u check eder ve ilk hamle yapilmissa hic döngüye girmeden devam eder
        if (_count == 0) {
            for (int i = 0; i < getWidth(); ++i) {
                for (int j = 0; j < getHeight(); ++j) {
                    if (gameBoard[i][j].getPosition() == 'O')
                        _count += 1;
                }
            }
        }
        // eger ilk hamle yapilmamissa yapar
        if (_count == 0)
            firstComputerMove();
        else {
            // once user1 i engellemeye calisir
            result = blockX();
            // engellenecek hamle yoksa kendi kazanmaya calisir
            if (result == 0) {
                if (diagMove() != -1)
                    return 1;
            }
        }
        if (result > 0) {
            cout << "Computer ->" << endl << endl;
            printBoard();
            return 0;
        }
        cout << "Computer ->" << endl << endl;
        printBoard();
        return 1;
    }

    int ConnectFourDiag::diagMove() {
        for (int i = 0; i < getWidth(); ++i) {        // dikey
            for (int j = 0; j < getHeight(); ++j) {   // yatay
                if (gameBoard[i][j].getPosition() == 'O') {
                    /*------------------------------------------------------------------------------*/
                    // sag capraz icin
                    // sag yukari capraz
                    if (gameBoard[i - 1][j + 1].getPosition() == '.' &&
                        gameBoard[i][j + 1].getPosition() != '.') {
                        gameBoard[i - 1][j + 1].setPosition('O');
                        appendUndoArr(i - 1);
                        cout << "Computer ->" << endl << endl;
                        printBoard();
                        return 1;
                    }
                    if (gameBoard[i - 1][j + 1].getPosition() != '.' &&
                        gameBoard[i + 1][j - 1].getPosition() == '.' &&
                        gameBoard[i + 2][j - 1].getPosition() != '.') {
                        gameBoard[i + 1][j - 1].setPosition('O');
                        appendUndoArr(i + 1);
                        cout << "Computer ->" << endl << endl;
                        printBoard();
                        return 1;
                    }
                    /*------------------------------------------------------------------------------*/
                    // sol capraz icin
                    if (gameBoard[i + 1][j - 1].getPosition() == '.' &&
                        gameBoard[i + 2][j - 1].getPosition() != '.') {
                        gameBoard[i + 1][j - 1].setPosition('O');
                        appendUndoArr(i + 1);
                        cout << "Computer ->" << endl << endl;
                        printBoard();
                        return 1;
                    }
                    if (gameBoard[i + 1][j - 1].getPosition() != '.' &&
                        gameBoard[i + 1][j + 1].getPosition() == '.' &&
                        gameBoard[i + 2][j + 1].getPosition() != '.') {
                        gameBoard[i + 1][j + 1].setPosition('O');
                        appendUndoArr(i + 1);
                        cout << "Computer ->" << endl << endl;
                        printBoard();
                        return 1;
                    }
                }
            }
        }
        return -1;
    }

    void ConnectFourDiag::play(int &lineLength) {
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
                        appendUndoArr(location);
                    } else if (_player == 2) {        // user2
                        gameBoard[location][getMoveLetter() - 97].setPosition('O');
                        appendUndoArr(location);
                    }
                    cout << "User -> " << _player << endl << endl;
                }
            }
            printBoard();
        }
    }

    int ConnectFourDiag::startGame() {
        const int player1 = 1, player2 = 2;
        int user = 'p', computer = 'c', lineLength;

        // user-user
        if (_choice == user) {
            while (true) {
                _player = player1;
                play(lineLength);
                // win funct
                if (win()) {
                    cout << endl << "USER " << player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                    _game = true;
                    return 1;
                }
                cout << "-------------------------------------------------------------" << endl;
                _player = player2;
                play(lineLength);
                // win
                if (win()) {
                    cout << endl << "USER " << player2 << " WON!!" << endl;         // user2 kazanir ve oyun biter
                    _game = true;
                    return 1;
                }
                cout << "-------------------------------------------------------------" << endl;
                if (checkFullBoard(lineLength)) {
                    cerr << "There is no empty space on the board." << endl;
                    _game = true;
                    return 1;
                }

            }
        }
            // user-computer
        else if (_choice == computer) {
            while (true) {
                _player = player1;
                play(lineLength);
                // win funct
                if (win()) {
                    cout << endl << "USER " << player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                    _game = true;
                    return 1;
                }
                cout << "-------------------------------------------------------------" << endl;
                play();
                // win
                if (win()) {
                    cout << endl << "COMPUTER WON!!" << endl;                       // computer kazanir ve oyun biter
                    _game = true;
                    return 1;
                }
                cout << "-------------------------------------------------------------" << endl;
                if (checkFullBoard(lineLength)) {
                    cerr << "There is no empty space on the board." << endl;
                    _game = true;
                    return 1;
                }
            }
        }
    }

    int ConnectFourDiag::loadGame(string fileName, int &loadPlayer, int lineLength) {
        int ply, sizeH, sizeW;
        char ch;

        ifstream file(fileName);
        if (file.is_open()) {
            if (file.peek() == ifstream::traits_type::eof()) {
                cerr << "File is empty" << endl;
                return -1;
            }
            file >> ch;
            _choice = ch;
            file >> ply;
            _player = ply;

            file >> sizeH;
            file >> sizeW;


            if (getWidth() != sizeW && getHeight() != sizeH) {
                for (int m = 0; m < getWidth() + 1; ++m)
                    delete[] gameBoard[m];
                delete[] gameBoard;

                gameBoard = nullptr;

                setHeight(sizeH + 1);
                setWidth(sizeW + 1);
                arrAllocation();

            }

            string line;
            int i = 0;

            getline(file, line); // for empty line -- ignore this
            while (getline(file, line)) {
                for (int j = 0; j < line.length(); j++, i++)
                    gameBoard[i][j].setPosition((line[j]));
            }
            file.close();
            cout << "Game Loaded!" << endl;
            printBoard();
        } else
            return -1;

        cout << "Player " << currentPlayer() << endl;
        loadPlayer = currentPlayer();

        if (getChoice() == 'c')
            playGame();
        else {
            if (currentPlayer() == 2) {
                // 2.oyuncuysa ilk hamleyi yapar sonra diger fonk da devam eder.
                play(lineLength);
                // win funct
                if (win()) {
                    cout << endl << "USER " << currentPlayer() << " WON!!" << endl;     // user2 kazanir ve oyun biter
                    exit(1);
                }
                cout << "-------------------------------------------------------------" << endl;
            }
            playGame();
        }
    }
}