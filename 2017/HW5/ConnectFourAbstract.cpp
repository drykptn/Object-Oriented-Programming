//
// Created by derya on 27.11.2017.
//

#include "ConnectFourAbstract.h"

namespace Zeytin {

    ConnectFourAbstract::ConnectFourAbstract() : _count(0), _game(false) {
    /* Intentionally empty */ }

    ConnectFourAbstract::ConnectFourAbstract(int w, int h) : _count(0), _game(false) {
        setWidth(w);
        setHeight(h);
        arrAllocation();
    }

    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract &other) {
        for (int i = 0; i < getWidth(); ++i)
            delete [] gameBoard[i];
        delete [] gameBoard;

        gameBoard = nullptr;

        setWidth(other.getWidth());
        setHeight(other.getHeight());
        arrAllocation();

        for (int j = 0; j < getWidth(); ++j) {
            for (int i = 0; i < getHeight(); ++i)
                gameBoard[j][i].setPosition(other.gameBoard[j][i].getPosition());
        }
    }

    ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract &other) {

        if(getWidth() != other.getWidth() || getHeight() != other.getHeight()){
            for (int i = 0; i < getWidth(); ++i)
                delete [] gameBoard[i];
            delete [] gameBoard;

            gameBoard = nullptr;

            setWidth(other.getWidth());
            setHeight(other.getHeight());
            arrAllocation();
        }

        for (int j = 0; j < getWidth() ; ++j) {
            for (int i = 0; i < getHeight() ; ++i)
                gameBoard[j][i].setPosition(other.gameBoard[j][i].getPosition());
        }
        return *this;
    }


    ConnectFourAbstract::~ConnectFourAbstract() {
        for (int i = 0; i < getHeight(); ++i)
            delete [] gameBoard[i];
        delete [] gameBoard;
    }

    // User selects the game.
    void ConnectFourAbstract::selectGame() {
        char ch;
        cout << "Please select a game." << endl;
        cout << "Player | Computer | Exit " << endl;
        cin >> ch;
        _choice = static_cast<char>(tolower(ch));

        if (_choice != 'p' && _choice != 'c' && _choice != 'e') {
            cerr << "Please try again." << endl;
            selectGame();
        }
    }

    int ConnectFourAbstract::saveGame(const string &fileName) const {
        ofstream file;
        file.open(fileName);
        cout << fileName;
        if (file.is_open()) {
            file << getChoice() << " ";
            file << currentPlayer() << " ";
            file << getHeight() << " ";
            file << getWidth();
            file << endl;

            for (int i = 0; i < getWidth(); ++i) {
                for (int j = 0; j < getHeight(); ++j)
                    file << gameBoard[i][j].getPosition();
                file << endl;
            }
            file.close();
        } else
            return -1;
    }

    void ConnectFourAbstract::setHeight(int num) {
        _height = num;
    }

    void ConnectFourAbstract::setWidth(int num) {
        _width = num;
    }

    void ConnectFourAbstract::arrAllocation() {
        gameBoard = new Cell *[getWidth() + 1];
        undo = new int[getHeight() * getWidth() + 1];
        for (int i = 0; i < getWidth() + 1; ++i)
            gameBoard[i] = new Cell[getHeight() + 1];

        for (int j = 0; j < getWidth() * getHeight(); ++j)
            undo[j] = -1;
    }

// eger board da her yer dolar ve kimse kazanamazsa diye board u check eder
    bool ConnectFourAbstract::checkFullBoard(int &lineLength) {
        if (lineLength <= 1) {
            for (int i = 0; i < getHeight(); ++i) {
                _moveLetter = static_cast<char>(i + 97);
                if (findLocation(lineLength) != -1)
                    return false;
            }
            return true;
        }
        return false;
    }

    void ConnectFourAbstract::printBoard() const {
        // for letters
        for (char letter = 'a'; letter < 'a' + getHeight(); ++letter)
            cout << letter << " ";
        cout << endl;
        // for squares
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                cout << gameBoard[i][j].getPosition() << " ";
            }
            cout << endl;
        }
    }

    bool ConnectFourAbstract::win() {
        // yatay icin user1    // yatay icin user2
        if (winControl('X') || winControl('O'));
    }

    int ConnectFourAbstract::appendUndoArr(int x) {
        int findSizeOf = findLastLocation();
        if (findSizeOf != -1)
            undo[findSizeOf] = x;
    }

    int ConnectFourAbstract::findLastLocation() {
        for (int i = 0; i < getHeight() * getWidth(); ++i) {
            if (undo[i] == -1)
                return i;
        }
        return -1;
    }

    void ConnectFourAbstract::firstComputerMove() {
        gameBoard[getWidth() - 1][getHeight() / 2].setPosition('O');
        appendUndoArr(getHeight() / 2);

        if (gameBoard[getWidth() - 1][getHeight() / 2].getPosition() == 'X') {
            gameBoard[getWidth() - 1][getHeight() / 2 + 1].setPosition('O');
            appendUndoArr(getHeight() / 2 + 1);
        }
    }

    int ConnectFourAbstract::takeMove(int &error, string &filename, int &saveOrLoadOrUndo, int &lineLength) {
        error = 0;
        string line, token, fName, delimiter = " ";
        cout << "Enter your move" << endl;

        getline(cin, line);

        // bir tane fazladan bos karakter aliyor. Onu engellemek icin 2 defa getline kullanildi
        while (line.length() == 0)
            getline(cin, line);

        for (int k = 0; k < line.length(); ++k)
            line[k] = static_cast<char>(tolower(line[k]));

        // parse string
        token = line.substr(0, line.find(delimiter));
        line.erase(0, line.find(delimiter) + delimiter.length());
        fName = line.substr(0, line.find(delimiter));

        lineLength = static_cast<int>(line.length());

        if (line[0] < 97 || line[0] > 122) {
            cerr << "Please enter a letter" << endl;
            return -1;
        }

        if (line.length() > 1) {
            if (token.compare("undo") == 0)
                saveOrLoadOrUndo = 3;
            if (token.compare("save") == 0) {
                filename = fName;
                saveOrLoadOrUndo = 1;
            }
            if (token.compare("load") == 0) {
                filename = fName;
                saveOrLoadOrUndo = 2;
            }
            if (!(saveOrLoadOrUndo == 1 || saveOrLoadOrUndo == 2 || saveOrLoadOrUndo == 3)) {
                cerr << "You entered wrong input" << endl;
                return -1;
            }
        }

        _moveLetter = static_cast<char>(tolower(line[0]));

        // if user entered wrong letter
        if (line.length() <= 1) {
            if (getMoveLetter() < 97 || getMoveLetter() >= 97 + getHeight())
                error = -1;             // board size i disinda letter girerse
        }
    }

    // sutunda bos olan yeri return eder. Doluysa -1 return eder
    int ConnectFourAbstract::findLocation(int lineLength) {
        if (lineLength <= 1) {
            for (int i = getWidth(); i >= 0; i--) {
                if (gameBoard[i][getMoveLetter() - 97].getPosition() == '.')
                    return i;
            }
            return -1;
        }
        return 2;
    }

    void ConnectFourAbstract::checkMove(const int &error, const int &location, bool &control) {
        // if user enter wrong input
        if (error == -1) {
            cerr << "You entered wrong letter.Please try again!" << endl;
            control = false;
        }
            // if user _choice a full column
        else if (location == -1) {
            cerr << "This column is full. Please try another column." << endl;
            control = false;
        }
    }

    void ConnectFourAbstract::initializeBoard() {
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                gameBoard[i][j].setPosition('.');
            }
        }
    }

    // Takes input from user and checks input. Then, sent to setter functions.
    void ConnectFourAbstract::takeBoardSize() {
        int num = 0;

        cout << "Please enter a width" << endl;
        cin >> num;
        // board width ini check eder
        if (testBoardSize(num) == 1) {
            setHeight(num);
            cout << "Please enter a height" << endl;
            cin >> num;
            // board height ini check eder
            if (testBoardSize(num) == 1)
                setWidth(num);
            else
                exit(1);
        } else
            exit(1);
    }

    // This function tests height/width of board
    int ConnectFourAbstract::testBoardSize(int num) {
        if (num < 4) {
            cout << "Board width/height is not smaller than 4" << endl;
            exit(1);
        } else if (num > 32) {
            cout << "Board width/height is not bigger than 32" << endl;
            exit(1);
        }
        return 1;
    }
}