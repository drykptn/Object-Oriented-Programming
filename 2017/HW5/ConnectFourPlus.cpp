//
// Created by derya on 22.11.2017.
//

#include "ConnectFourPlus.h"
#include "ConnectFourPlusUndo.h"

namespace Zeytin {

    int ConnectFourPlus::playGame() {
        takeBoardSize();
        arrAllocation();
        initializeBoard();
        selectGame();
        printBoard();
        startGame();
    }

    bool ConnectFourPlus::winControl(char user) {
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                // yatay user1 - user2
                if (gameBoard[i][j].getPosition() == user) {
                    if (j + 1 <= getHeight() && gameBoard[i][j + 1].getPosition() == user) {
                        if (j + 2 <= getHeight() && gameBoard[i][j + 2].getPosition() == user) {
                            if (j + 3 <= getHeight() && gameBoard[i][j + 3].getPosition() == user) {
                                cout << "-------------------------------------------------------------" << endl;
                                cout << endl << "FINAL BOARD !! " << endl;
                                for (int k = 0; k < 4; ++k)
                                    gameBoard[i][j + k].setPosition(static_cast<char>(tolower(
                                            gameBoard[i][j +
                                                         k].getPosition())));   // kazanirsa harfleri kucuge cevirir.
                                printBoard();
                                return true;
                            }
                        }
                    }
                }
                // dikey user1 - user2
                if (gameBoard[i][j].getPosition() == user) {
                    if (i + 1 <= getWidth() && gameBoard[i + 1][j].getPosition() == user) {
                        if (i + 2 <= getWidth() && gameBoard[i + 2][j].getPosition() == user) {
                            if (i + 3 <= getWidth() && gameBoard[i + 3][j].getPosition() == user) {
                                cout << "-------------------------------------------------------------" << endl;
                                cout << endl << "FINAL BOARD !! " << endl;
                                for (int k = 0; k < 4; ++k)
                                    gameBoard[i + k][j].setPosition(static_cast<char>(tolower(
                                            gameBoard[i +
                                                      k][j].getPosition())));   // kazanirsa harfleri kucuge cevirir.
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

    int ConnectFourPlus::plusMove() {
        for (int i = 0; i < getWidth(); ++i) {        // dikey
            for (int j = 0; j < getHeight(); ++j) {   // yatay
                if (gameBoard[i][j].getPosition() == 'O') {
                    /*------------------------------------------------------------------------------*/
                    // yatay icin
                    if (gameBoard[i][j + 1].getPosition() == '.' &&
                        gameBoard[i + 1][j + 1].getPosition() != '.') {
                        gameBoard[i][j + 1].setPosition('O');
                        appendUndoArr(j + 1);
                        cout << "Computer ->" << endl << endl;
                        printBoard();
                        return 1;       // loop tan cikabilsin diye
                    }
                    if (gameBoard[i][j + 1].getPosition() != '.' &&
                        gameBoard[i][j - 1].getPosition() == '.' &&
                        gameBoard[i + 1][j - 1].getPosition() != '.') {
                        gameBoard[i][j - 1].setPosition('O');
                        appendUndoArr(j - 1);
                        cout << "Computer ->" << endl << endl;
                        printBoard();
                        return 1;       // loop tan cikabilsin diye
                    }
                    /*------------------------------------------------------------------------------*/
                    // dikey icin
                    if (gameBoard[i - 1][j].getPosition() == '.') {
                        gameBoard[i - 1][j].setPosition('O');
                        appendUndoArr(j);
                        cout << "Computer ->" << endl << endl;
                        printBoard();
                        return 1;
                    }

                }
            }
        }
        return -1;
    }

    int ConnectFourPlus::play() {
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
                if (plusMove() != -1)
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

    int ConnectFourPlus::blockX() {
        int result = 0;
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                if (gameBoard[i][j].getPosition() == 'X') {
                    /*------------------------------------------------------------------------------*/
                    // dikey icin
                    if (gameBoard[i - 1][j].getPosition() == 'X') {
                        if (gameBoard[i - 2][j].getPosition() == '.') {
                            gameBoard[i - 2][j].setPosition('O');
                            return 1;
                        }
                    }
                        /*------------------------------------------------------------------------------*/
                        // yatay icin
                    else if (gameBoard[i][j + 1].getPosition() == 'X') {
                        if (gameBoard[i][j + 2].getPosition() == '.') {
                            if (gameBoard[i + 1][j + 2].getPosition() != '.') {
                                gameBoard[i][j + 2].setPosition('O');
                                return 1;
                            } else if (gameBoard[i][j - 1].getPosition() == '.' &&
                                       gameBoard[i + 1][j - 1].getPosition() != '.') {
                                gameBoard[i][j - 1].setPosition('O');
                                return 1;
                            }
                        }
                    }
                }
            }
        }
        return result;
    }

    void ConnectFourPlus::play(int &lineLength) {
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

    int ConnectFourPlus::startGame() {
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

    int ConnectFourPlus::loadGame(string fileName, int &loadPlayer, int lineLength) {
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

                setHeight(sizeH);
                setWidth(sizeW);
                arrAllocation();

            }

            string line;
            int i = 0;
            getline(file, line); // for empty line -- ignore this

            while (getline(file, line)) {
                for (int j = 0; j < line.length() + 1; j++) {
                    gameBoard[i][j].setPosition((line[j]));
                }
                i++;
            }
            file.close();
            cout << "Game Loaded!" << endl;
            printBoard();
        } else
            return -1;

        cout << "Player " << currentPlayer() << endl;
        loadPlayer = currentPlayer();

        if (getChoice() == 'c')
            startGame();
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