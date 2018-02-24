//
// Created by derya on 01.11.2017.
//

#include "ConnectFour.h"

enum CellType { empty = 0, user1 = 1, user2 = 2, computer = 3};

/*-------------------------------------------------------------------------------------------------------------------*/
/*                                      Static declaration and functions                                             */
/*-------------------------------------------------------------------------------------------------------------------*/

int ConnectFour::livingCell = 0;

int ConnectFour::getLivingCell() {
    return  livingCell;
}
void ConnectFour::setLivingCell() {
    livingCell++;
}
/*-------------------------------------------------------------------------------------------------------------------*/
/*                                       Constructors/destructor                                                     */
/*-------------------------------------------------------------------------------------------------------------------*/


ConnectFour::ConnectFour():count(0), game(false), twoLetter(0) {
    setHeight(5);
    setWidth(5);
    arrAllocation();
}

ConnectFour::ConnectFour(char mode):count(0), game(false), twoLetter(0){
    setGameMode(mode);
}

ConnectFour::ConnectFour(string filename):count(0), game(false), twoLetter(0) {
    readFileBoard();
}

ConnectFour::ConnectFour(int w , int h):count(0), game(false), twoLetter(0) {
    setWidth(w);
    setHeight(h);
    arrAllocation();
}
// copy const
ConnectFour::ConnectFour(const ConnectFour &other) {
    for (int i = 0; i < getWidth() + 1; ++i)
        delete [] gameBoard[i];
    delete [] gameBoard;

    gameBoard = nullptr;

    setWidth(other.getWidth());
    setHeight(other.getHeight());
    arrAllocation();

    for (int j = 0; j < getWidth() + 1; ++j) {
        for (int i = 0; i < getHeight() + 1; ++i)
            gameBoard[j][i].setPosition(other.gameBoard[j][i].getPosition());
    }

}
// destructor
ConnectFour::~ConnectFour() {

    for (int i = 0; i < getWidth() + 1; ++i)
        delete [] gameBoard[i];
    delete [] gameBoard;

    gameBoard = nullptr;

}


/*-------------------------------------------------------------------------------------------------------------------*/
/*                                      Overload functions                                                           */
/*-------------------------------------------------------------------------------------------------------------------*/

ConnectFour& ConnectFour::operator=(const ConnectFour &other) {

    if(getWidth() != other.getWidth() || getHeight() != other.getHeight()){
        for (int i = 0; i < getWidth() + 1; ++i)
            delete [] gameBoard[i];
        delete [] gameBoard;

        gameBoard = nullptr;

        setWidth(other.getWidth());
        setHeight(other.getHeight());
        arrAllocation();
    }

    for (int j = 0; j < getWidth() + 1; ++j) {
        for (int i = 0; i < getHeight() + 1; ++i)
            gameBoard[j][i].setPosition(other.gameBoard[j][i].getPosition());
    }
    return *this;
}

bool ConnectFour::Cell::operator==(const Cell &other) const {
    if(getPosition() == other.getPosition())
    return false;
}

ConnectFour::Cell ConnectFour::Cell::operator++() {
    if(getPosition() == empty)
        setPosition(user1);
    if(getPosition() == user1)
        setPosition(user2);
    if(getPosition() == user2)
        setPosition(computer);
    if(getPosition() == computer)
        setPosition(empty);

    return *this;
}

ConnectFour::Cell ConnectFour::Cell::operator--() {
    if(getPosition() == user1)
        setPosition(empty);
    if(getPosition() == user2)
        setPosition(user1);
    if(getPosition() == computer)
        setPosition(user2);
    if(getPosition() == empty)
        setPosition(computer);
    return *this;
}

ConnectFour::Cell ConnectFour::Cell::operator++(int) {
    Cell temp(*this);
    operator ++();
    return temp;
}

ConnectFour::Cell ConnectFour::Cell::operator--(int) {
    Cell temp(*this);
    operator --();
    return temp;
}
ostream& operator <<(ostream &outputStream, ConnectFour::Cell const& c) {
    outputStream << "Position -> " << c.getPosition();
    return outputStream;
}
istream& operator >>(istream &inputStream, ConnectFour::Cell &c) {
    char sign;
    inputStream >> sign;
    c.setPosition(sign);
    return inputStream;
}

bool ConnectFour::operator >=(const ConnectFour& other)const{
    if(getTwoLetter() >= other.getTwoLetter() );
}


bool ConnectFour::operator ==(const ConnectFour &other) const {
    if(getHeight() == other.getHeight() && getWidth() == other.getWidth()){
        for (int i = 0; i < getWidth() + 1; ++i) {
            for (int j = 0; j < getHeight() + 1; ++j) {
                if(gameBoard[i][j].getPosition() != other.gameBoard[i][j].getPosition())
                    return false;           // esit degilse cikar
            }
        }
        return true;
    }
    return false;
}

bool ConnectFour::operator !=(const ConnectFour &other) const {
    if(!(*this == other));
}

/*-------------------------------------------------------------------------------------------------------------------*/

void ConnectFour::Cell::setPosition(char letter) {
    position = letter;
}

void ConnectFour::setHeight(int num) {
    height = num;
}

void ConnectFour::setWidth(int num) {
    width = num;
}

void ConnectFour::setPlayer(int num) {
    player = num;
}

void ConnectFour::setGameMode(char mode) {
    gameMode = static_cast<char>(tolower(mode));
    checkGameMode();
}

void ConnectFour::startGame(){
    readFileBoard();
    selectGame();
    printBoard();
}

// User selects the game.
void ConnectFour::selectGame(){
    char ch;
    cout << "Please select a game." << endl;
    cout << "Player | Computer | Exit " << endl;
    cin >> ch;
    choice = static_cast<char>(tolower(ch));

    if(choice != 'p' && choice != 'c' && choice != 'e') {
        cerr << "Please try again." << endl;
        selectGame();
    }
}

void ConnectFour::play(int& lineLength) {
    int error = 0, saveOrLoad = 0, loadPlayer;
    string filename;
    bool control, loop = true;

    loadPlayer = player;

    while (loop) {
        control = true;
        saveOrLoad = 0;
        // hamleyi al
        if(takeMove(error, filename, saveOrLoad, lineLength) == -1 )
            takeMove(error, filename, saveOrLoad, lineLength);

        if(saveOrLoad == 1) {
            if(saveGame(filename) == -1)
                cerr << "The game could not saved" << endl;
            else
                cout << "The game saved." << endl;
        }
        else if(saveOrLoad == 2) {
            if(loadGame(filename, loadPlayer, lineLength) == -1)
                cout << "The game could not load" << endl;
            player = loadPlayer;
        }
        else {
            // konumu bul
            int location = findLocation(lineLength);

            // hamleyi check et
            checkMove(error, location, control);
            if(location == -1) {
                loop = false;
                control = false;
            }

            if (control && gameBoard[location][getMoveLetter() - 97].getPosition() == '*')   // dogruysa donguden cik ve board u print et
            {
                loop = false;
                if (player == 1) {             // user1
                    gameBoard[location][getMoveLetter() - 97].setPosition('X');
                    setLivingCell();
                } else if (player == 2) {       // user2
                    gameBoard[location][getMoveLetter() - 97].setPosition('O');
                    setLivingCell();
                }
                cout << "User -> " << player << endl << endl;
            }
        }
        printBoard();
    }
}


void ConnectFour::arrAllocation(){
    gameBoard = new Cell*[getWidth() + 1];
    for (int i = 0; i < getWidth() + 1; ++i)
        gameBoard[i] = new Cell[getHeight() + 1];
}

void ConnectFour::checkGameMode() {
    if(getGameMode() != 's' && getGameMode() != 'm'){
        cerr << "You entered wrong game mode!" << endl;
        char mode;
        cout << "Please select a game mode" << endl;
        cin >> mode;
        setGameMode(mode);
    }
}

int ConnectFour::findMaxLineInFile(string& filename){
    string line;
    int size = 0;
    ifstream fp(filename);
    if(fp.is_open()){
        while(getline(fp, line)) {
            if (line.length() > size)
                size = static_cast<int>(line.length());
        }
    }
    else
        return -1;
    fp.close();
    return size;
}
int ConnectFour::findSizeOfFile(string& filename) {
    int fileSize = 0;
    ifstream fptr(filename);
    if(fptr.is_open()) {
        char c;
        while (fptr.get(c))
            if (c == '\n')
                ++fileSize;
    }
    else
        return -1;
    fptr.close();
    return fileSize;
}

void ConnectFour::readFileBoard(){

    string line, filename;
    int lineSize = 0;
    int fileSize = 0;

    cout << "Please enter a filename" << endl;
    getline(cin, filename);

    // bir tane fazladan bos karakter aliyor. Onu engellemek icin 2 defa getline kullanildi
    while (filename.length() == 0)
        getline(cin, filename);

    size_t found = filename.find(".txt");
    if(found != string::npos) {
        fileSize = findSizeOfFile(filename);
        lineSize = findMaxLineInFile(filename);
        if(lineSize == -1 || fileSize == -1) {
            cerr << "You entered wrong filename" << endl;
            exit(1);
        }
        setWidth(fileSize);
        setHeight(lineSize);
        arrAllocation();
        initializeBoardFromFile(filename);
    }
}

void ConnectFour::initializeBoardFromFile(string filename) {
    string line;
    ifstream fp(filename);
    if(fp.is_open()) {
        int i = 0;
        while (getline(fp, line)) {
            for (int j = 0; j < line.length(); ++j)
                gameBoard[i][j].setPosition(line[j]);

            // board un disinda karakter engellememek icin geri kalan kisima empty space atar
            for (int k = line.length(); k < getHeight(); ++k)
                gameBoard[i][k].setPosition(' ');

            i++;
        }
        fp.close();
    }
    boardAssignEmptySpace();
}


void ConnectFour::printBoard() const {
    // for letters
    for (char letter = 'a'; letter < 'a' + getHeight(); ++letter)
        cout << letter << " ";
    cout << endl;
    // for squares
    for (int i = 0; i < getWidth() + 1; ++i) {
        for (int j = 0; j < getHeight() ; ++j) {
            cout << gameBoard[i][j].getPosition() << " ";
        }
        cout << endl;
    }
}
// eger board da her yer dolar ve kimse kazanamazsa diye board u check eder
bool ConnectFour::checkFullBoard(int& lineLength){
    if(lineLength <= 1) {
        for (int i = 0; i < getHeight(); ++i) {
            moveLetter = static_cast<char>(i + 97);
            if (findLocation(lineLength) != -1)
                return false;
        }
        return true;
    }
    return false;
}

// kazanan player in hamlesini check eder ve o hamleyi kucuk harflere cevirir
bool ConnectFour::winControl(char user){
    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            // yatay user1 - user2
            if( gameBoard[i][j].getPosition() == user) {
                if (gameBoard[i][j + 1].getPosition() == user) {
                    if (gameBoard[i][j + 2].getPosition() == user) {
                        twoLetter++;
                        if (gameBoard[i][j + 3].getPosition() == user) {
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                gameBoard[i][j + k].setPosition(static_cast<char>(tolower(gameBoard[i][j + k].getPosition())));   // kazanirsa harfleri kucuge cevirir.
                            printBoard();
                            return true;
                        }
                    }
                }
            }
            // dikey user1 - user2
            if( gameBoard[i][j].getPosition() == user){
                if(gameBoard[i+1][j].getPosition() == user){
                    if(gameBoard[i+2][j].getPosition() == user){
                        twoLetter++;
                        if(gameBoard[i+3][j].getPosition() == user){
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                gameBoard[i + k][j].setPosition(static_cast<char>(tolower(gameBoard[i + k][j].getPosition())));   // kazanirsa harfleri kucuge cevirir.
                            printBoard();
                            return true;
                        }
                    }
                }
            }
            // sag capraz user1 - user2
            if( gameBoard[i][j].getPosition() == user){
                if(gameBoard[i-1][j+1].getPosition() == user){
                    if( gameBoard[i-2][j+2].getPosition() == user){
                        twoLetter++;
                        if(gameBoard[i-3][j+3].getPosition() == user) {
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                gameBoard[i - k][j + k].setPosition(static_cast<char>(tolower(gameBoard[i - k][j + k].getPosition())));   // kazanirsa harfleri kucuge cevirir.
                            printBoard();
                            return true;
                        }
                    }
                }
            }
            // sol capraz user1 - user2
            if( gameBoard[i][j].getPosition() == user){
                if(gameBoard[i-1][j-1].getPosition() == user){
                    if(gameBoard[i-2][j-2].getPosition() == user){
                        twoLetter++;
                        if(gameBoard[i-3][j-3].getPosition() == user) {
                            cout << endl << "FINAL BOARD !! " << endl;
                            cout << "-------------------------------------------------------------" << endl;
                            for (int k = 0; k < 4; ++k)
                                gameBoard[i - k][j - k].setPosition(static_cast<char>(tolower(gameBoard[i - k][j - k].getPosition())));   // kazanirsa harfleri kucuge cevirir.
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
bool ConnectFour::win(){
    // yatay icin user1    // yatay icin user2
    if (winControl('X') || winControl('O'));
}

void ConnectFour::checkMove(const int& error, const int& location, bool& control){
    // if user enter wrong input
    if(error == -1) {
        cerr << "You entered wrong letter.Please try again!" << endl;
        control = false;
    }
        // if user choice a full column
    else if(location == -1){
        cerr << "This column is full. Please try another column." << endl;
        control = false;
    }
}

int ConnectFour::takeMove(int& error, string& filename, int& saveOrLoad, int& lineLength) {
    char temp1[10], temp2[10];
    error = 0;
    string line, temp;
    cout << "Enter your move" << endl;

    getline(cin, line);

    // bir tane fazladan bos karakter aliyor. Onu engellemek icin 2 defa getline kullanildi
    while (line.length() == 0)
        getline(cin, line);

    lineLength = static_cast<int>(line.length());

    for (int k = 0; k < line.length(); ++k)
        line[k] = static_cast<char>(tolower(line[k]));

    if( line[0] < 97 || line[0] > 122) {
        cerr << "Please enter a letter" << endl;
        return -1;
    }

    if (line.length() > 1) {
        // if user entered wrong input
        size_t found = line.rfind(' ');
        if(found == string::npos){
            cerr << "You entered wrong input" << endl;
            return -1;
        }

        int i, j;
        for (i = 0; line[i] != ' '; ++i)
            temp1[i] = line[i];
        temp1[i] = '\0';

        for (j = 0; line[i + 1] != '\0'; ++j, i++)
            temp2[j] = line[i + 1];
        temp2[j] = '\0';

        if (strcmp("save", temp1) == 0) {
            filename = temp2;
            saveOrLoad = 1;
        }
        else if (strcmp("load", temp1) == 0) {
            filename = temp2;
            saveOrLoad = 2;
        }
    }

    moveLetter = static_cast<char>(tolower(line[0]));

    // if user entered wrong letter
    if (line.length() <= 1) {
        if (getMoveLetter() < 97 || getMoveLetter() >= 97 + getHeight())
            error = -1;                            // board size i disinda letter girerse
    }
}

// dosyadan okunan boardda farkli degerler gelmesin diye '*' olmayan yerlere ' ' empty space atar.
void ConnectFour::boardAssignEmptySpace(){
    for (int i = 0; i < getWidth() + 1; ++i) {
        for (int j = 0; j < getHeight() + 1; ++j) {
            if(gameBoard[i][j].getPosition() != '*')
                gameBoard[i][j].setPosition(' ');
        }
    }
}


// sutunda bos olan yeri return eder. Doluysa -1 return eder
int ConnectFour::findLocation(int lineLength){
    if(lineLength <= 1) {
        for (int i = getWidth(); i >= 0; i--) {
            if (gameBoard[i][getMoveLetter() - 97].getPosition() == '*')
                return i;
        }
        return -1;
    }
    return 2;
}

int ConnectFour::playGame() {
    const int player1 = 1, player2 = 2;
    int user = 'p', computer = 'c', lineLength;

    // user-user
    if (choice == user) {
        while(true) {
            setPlayer(player1);
            play(lineLength);
            // win funct
            if(win()) {
                cout << endl  <<"USER "<< player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            setPlayer(player2);
            play(lineLength);
            // win
            if(win()) {
                cout << endl << "USER "<< player2 << " WON!!" << endl;         // user2 kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            if(checkFullBoard(lineLength)){
                cerr << "There is no empty space on the board." << endl;
                game = true;
                return 1;
            }
            cout << "Living Cell: " << getLivingCell() << endl << endl;

            if(getGameMode() == 'm')
                return 2;
        }
    }
    // user-computer
    else if (choice == computer) {
        while(true) {
            setPlayer(player1);
            play(lineLength);
            // win funct
            if (win()) {
                cout << endl << "USER " << player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            play();
            // win
            if (win()) {
                cout << endl << "COMPUTER WON!!" << endl;                       // computer kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            if (checkFullBoard(lineLength)) {
                cerr << "There is no empty space on the board." << endl;
                game = true;
                return 1;
            }
            cout << "Living Cell: " << getLivingCell() << endl << endl;

            if(getGameMode() == 'm')
                return 2;
        }
    }
}
int ConnectFour::blockX() {
    int result = 0;
    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            if (gameBoard[i][j].getPosition() == 'X') {
                /*------------------------------------------------------------------------------*/
                // dikey icin
                if (gameBoard[i - 1][j].getPosition() == 'X'){
                    if(gameBoard[i - 2][j].getPosition() == '*') {
                        gameBoard[i - 2][j].setPosition('O');
                        setLivingCell();
                        return 1;
                    }
                }
                /*------------------------------------------------------------------------------*/
                // yatay icin
                else if (gameBoard[i][j + 1].getPosition() == 'X') {
                    if (gameBoard[i][j + 2].getPosition() == '*') {
                        if (gameBoard[i + 1][j + 2].getPosition() != '*') {
                            gameBoard[i][j + 2].setPosition('O');
                            setLivingCell();
                            return 1;
                        }
                        else if (gameBoard[i][j - 1].getPosition() == '*' &&
                                 gameBoard[i + 1][j - 1].getPosition() != '*') {
                            gameBoard[i][j - 1].setPosition('O');
                            setLivingCell();
                            return 1;
                        }
                    }
                }
                /*------------------------------------------------------------------------------*/
                // sag capraz icin
                else if (gameBoard[i - 1][j + 1].getPosition() == 'X' &&
                         gameBoard[i - 2][j + 2].getPosition() == '*') {
                    if (gameBoard[i - 1][j + 2].getPosition() != '*') {
                        gameBoard[i - 2][j + 2].setPosition('O');
                        setLivingCell();
                        return 1;
                    }
                    else if (gameBoard[i + 1][j - 1].getPosition() == '*' &&
                             gameBoard[i + 2][j - 1].getPosition() != '*') {
                        gameBoard[i + 1][j - 1].setPosition('O');
                        setLivingCell();
                        return 1;
                    }
                }
                /*------------------------------------------------------------------------------*/
                // sol capraz icin
                else if (gameBoard[i - 1][j - 1].getPosition() == 'X' &&
                         gameBoard[i - 2][j - 2].getPosition() == '*'){
                    if (gameBoard[i - 1][j - 2].getPosition() != '*') {
                        gameBoard[i - 2][j - 2].setPosition('O');
                        setLivingCell();
                        return 1;
                    }
                    else if (gameBoard[i + 1][j + 1].getPosition() == '*' &&
                             gameBoard[i + 2][j + 1].getPosition() != '*') {
                        gameBoard[i + 1][j + 1].setPosition('O');
                        setLivingCell();
                        return 1;
                    }
                }
            }
        }
    }
    return result;
}
void ConnectFour::firstComputerMove(){
    gameBoard[getWidth()-1][getHeight()/2].setPosition('O');
    setLivingCell();

    if( gameBoard[getWidth()-1][getHeight()/2].getPosition() == 'X' ) {
        gameBoard[getWidth() - 1][getHeight() / 2 + 1].setPosition('O');
        setLivingCell();
    }
}
int ConnectFour::play() {
    int result = 0;
    // board u check eder ve ilk hamle yapilmissa hic döngüye girmeden devam eder
    if(count == 0) {
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                if (gameBoard[i][j].getPosition() == 'O')
                    count += 1;
            }
        }
    }
    // eger ilk hamle yapilmamissa yapar
    if (count == 0 )
        firstComputerMove();
    else {
        // once user1 i engellemeye calisir
        result = blockX();
        // engellenecek hamle yoksa kendi kazanmaya calisir
        if(result == 0) {
            for (int i = 0; i < getWidth(); ++i) {        // dikey
                for (int j = 0; j < getHeight(); ++j) {   // yatay
                    if (gameBoard[i][j].getPosition() == 'O') {
                        /*------------------------------------------------------------------------------*/
                        // yatay icin
                        if (gameBoard[i][j + 1].getPosition() == '*' &&
                            gameBoard[i + 1][j + 1].getPosition() != '*') {
                            gameBoard[i][j + 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;       // loop tan cikabilsin diye
                        }
                        if (gameBoard[i][j + 1].getPosition() != '*' &&
                            gameBoard[i][j - 1].getPosition() == '*' &&
                            gameBoard[i + 1][j - 1].getPosition() != '*') {
                            gameBoard[i][j - 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;       // loop tan cikabilsin diye
                        }
                        /*------------------------------------------------------------------------------*/
                        // dikey icin
                        if (gameBoard[i - 1][j].getPosition() == '*') {
                            gameBoard[i - 1][j].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                        /*------------------------------------------------------------------------------*/
                        // sag capraz icin
                        // sag yukari capraz
                        if (gameBoard[i - 1][j + 1].getPosition() == '*' &&
                            gameBoard[i][j + 1].getPosition() != '*') {
                            gameBoard[i - 1][j + 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                        if (gameBoard[i - 1][j + 1].getPosition() != '*' &&
                            gameBoard[i + 1][j - 1].getPosition() == '*' &&
                            gameBoard[i + 2][j - 1].getPosition() != '*') {
                            gameBoard[i + 1][j - 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                        /*------------------------------------------------------------------------------*/
                        // sol capraz icin
                        if (gameBoard[i + 1][j - 1].getPosition() == '*' &&
                            gameBoard[i + 2][j - 1].getPosition() != '*') {
                            gameBoard[i + 1][j - 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                        if (gameBoard[i + 1][j - 1].getPosition() != '*' &&
                            gameBoard[i + 1][j + 1].getPosition() == '*' &&
                            gameBoard[i + 2][j + 1].getPosition() != '*') {
                            gameBoard[i + 1][j + 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                    }
                }
            }
        }
    }
    if(result > 0) {
        cout << "Computer ->" << endl << endl;
        printBoard();
        return 0;
    }
    cout << "Computer ->" << endl << endl;
    printBoard();
    return 1;
}


void ConnectFour::selectGameMode(){
    char mode;
    cout << "Please select a game mode" << endl;
    cin >> mode;
    setGameMode(mode);
}


int ConnectFour::saveGame(const string& fileName) const {
    ofstream file;
    file.open(fileName);
    if(file.is_open()) {
        file << getChoice() << " ";
        file << getPlayer() << " ";
        file << getHeight() << " ";
        file << getWidth();
        file << endl;

        for (int i = 0; i < getWidth() + 1; ++i) {
            for (int j = 0; j < getHeight() + 1; ++j)
                file << gameBoard[i][j].getPosition();
            file << endl;
        }
        file.close();
    }
    else
        return -1;
}

int ConnectFour::loadGame(string fileName, int& loadPlayer, int lineLength){
    int ply, sizeH, sizeW;
    char ch;

    ifstream file(fileName);
    if(file.is_open()){
        if ( file.peek() == ifstream::traits_type::eof() )
        {
            cerr << "File is empty" << endl;
            return -1;
        }
        file >> ch;     choice = ch;
        file >> ply;    player = ply;

        file >> sizeH;
        file >> sizeW;


        if(getWidth() != sizeW && getHeight() != sizeH) {
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
        livingCell = 0;
        while(getline(file, line)){
            for (int j = 0; j < line.length(); j++) {
                gameBoard[i][j].setPosition((line[j]));
                if(gameBoard[i][j].getPosition() == 'X' || gameBoard[i][j].getPosition() == 'O')
                    setLivingCell();
            }
            i++;
        }
        file.close();
        cout << "Game Loaded!" << endl;
        printBoard();
    }
    else
        return -1;

    cout << "Living Cell: " << getLivingCell() << endl << endl;

    cout << "Player " << getPlayer() << endl;
    loadPlayer = getPlayer();

    if(getChoice() == 'c')
        playGame();
    else{
        if(getPlayer() == 2){
            // 2.oyuncuysa ilk hamleyi yapar sonra diger fonk da devam eder.
            play(lineLength);
            // win funct
            if (win()) {
                cout << endl << "USER " << getPlayer() << " WON!!" << endl;     // user2 kazanir ve oyun biter
                exit(1);
            }
            cout << "-------------------------------------------------------------" << endl;
        }
        playGame();
    }
}

// This function tests height/width of board
int ConnectFour::testBoardSize(int num) {
    if(num < 5){
        cout << "Board width/height is not smaller than 5" << endl;
        exit(1);
    }
    else if( num > 32 ){
        cout << "Board width/height is not bigger than 32" << endl;
        exit(1);
    }
    return 1;
}


/*-------------------------------------------------------------------------------------------------------------------*/
/* These functions created for hw3 but not necessary for hw4 */
/*-------------------------------------------------------------------------------------------------------------------*/
void ConnectFour::initializeBoard() {
    for (int i = 0; i < getWidth() + 1 ; ++i) {
        for (int j = 0; j < getHeight() + 1 ; ++j) {
            gameBoard[i][j].setPosition('*');
        }
    }
}

// Takes input from user and checks input. Then, sent to setter functions.
void ConnectFour::takeBoardSize() {
    int num = 0;

    cout << "Please enter a width" << endl;
    cin >> num;
    // board width ini check eder
    if( testBoardSize(num) == 1 ) {
        setHeight(num);
        cout << "Please enter a height" << endl;
        cin >> num;
        // board height ini check eder
        if( testBoardSize(num) == 1 )
            setWidth(num);
        else
            exit(1);
    }
    else
        exit(1);
}


/*-------------------------------------------------------------------------------------------------------------------*/