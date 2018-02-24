#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

class ConnectFour{
public:
    // constructors
    ConnectFour();                    // default constructor
    ConnectFour(char mode);           // overload constructor
    // user direk filename ile contructor cagirirsa oyun load edilir ve kaldigi yerden devam eder.
    ConnectFour(string filename);

    // setter functions
    void setWidth(int num);
    void setHeight(int num);
    void setGameMode(char mode);
    void setPlayer(int num);
    void setChoice(char ch);
    void setMoveLetter(char letter);
    void setTwoLetter();

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
    static void setLivingCell();

    // others
    void selectGame();
    bool checkFullBoard(int& lineLenght);
    char toLower(char letter);
    void takeBoardSize();
    int testBoardSize(int num);
    void initializeBoard();
    bool win();
    bool winControl(char user);
    void printBoard();
    int saveGame(string fileName);
    int findLocation(int lineLength);
    void userMove(int& lineLength);
    int takeMove(int& error, string& filename, int& saveOrLoad, int& lineLength);
    void checkMove(const int& error, const int& location, bool& control);
    int playGame();
    int loadGame(string fileName, int& loadPlayer, int lineLength);
    int computerMove();
    void firstComputerMove();
    void checkGameMode();
    int blockX();
    void selectGameMode();

    // compare overload function
    bool operator >=( ConnectFour& other);

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

    // inner class
    class Cell{
    public:
        Cell(){}        // default constructor

        // setter functions
        void setPosition(char letter);

        // getter functions
        char getPosition();
    private:
        int row;        // 1,2,3..
        char position;   // A,B,C..
    };
    vector< vector<Cell> > gameCells;
};

int ConnectFour::livingCell = 0;

int main() {

    ConnectFour cf;
    cf.selectGameMode();

    if(cf.getGameMode() == 's') {
        cf.takeBoardSize();
        cf.initializeBoard();
        cf.selectGame();
        cf.printBoard();
        cf.playGame();
    }
    else if(cf.getGameMode() == 'm') {
        // multiple secim icin her objeye game modu set edilir
        ConnectFour object1(cf.getGameMode()), object2(cf.getGameMode()), object3(cf.getGameMode()),
                    object4(cf.getGameMode()), object5(cf.getGameMode());

        cout << "Obje 1" << endl;
        object1.takeBoardSize();
        object1.initializeBoard();
        object1.selectGame();
        object1.printBoard();

        cout << "Obje 2" << endl;
        object2.takeBoardSize();
        object2.initializeBoard();
        object2.selectGame();
        object2.printBoard();

        cout << "Obje 3" << endl;
        object3.takeBoardSize();
        object3.initializeBoard();
        object3.selectGame();
        object3.printBoard();

        cout << "Obje 4" << endl;
        object4.takeBoardSize();
        object4.initializeBoard();
        object4.selectGame();
        object4.printBoard();

        cout << "Obje 5" << endl;
        object5.takeBoardSize();
        object5.initializeBoard();
        object5.selectGame();
        object5.printBoard();

        int obj;
        int count = 0;
        bool goodOrBad;

        while(count < 5) {
            cout << "Choose an object: 1/2/3/4/5" << endl;
            cin >> obj;
            if (obj == 1) {
                if(object1.getGame() == true)
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object1.playGame();
                    goodOrBad = (object1 >= object2);
                    if(goodOrBad == true)
                        cout << "Object1 better than Object2" << endl;
                    else if(goodOrBad == false)
                        cout << "Object2 better than Object1" << endl;

                    if (object1.getGame() == true)
                        count += 1;
                }
            } else if (obj == 2) {
                if(object2.getGame() == true)
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object2.playGame();
                    if (object2.getGame() == true)
                        count += 1;
                }
            } else if (obj == 3) {
                if(object3.getGame() == true)
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object3.playGame();
                    if (object3.getGame() == true)
                        count += 1;
                }
            } else if (obj == 4) {
                if(object4.getGame() == true)
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object4.playGame();
                    if (object4.getGame() == true)
                        count += 1;
                }
            } else if (obj == 5) {
                if(object5.getGame() == true)
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object5.playGame();
                    if (object5.getGame() == true)
                        count += 1;
                }
            } else {
                cerr << "You entered wrong object" << endl;
                count = 10;
            }
        }
        if(count == 5)
            cout << "FINISH !!" << endl;
    }
    return 0;
}

int ConnectFour::getLivingCell() {
    return  livingCell;
}

void ConnectFour::setLivingCell() {
    livingCell++;
}

ConnectFour::ConnectFour():count(0), game(false), twoLetter(0)
{/* Intentionally empty */}

ConnectFour::ConnectFour(char mode):count(0), game(false), twoLetter(0){
    setGameMode(mode);
}

ConnectFour::ConnectFour(string filename):count(0), game(false), twoLetter(0) {
    int num = 0;
    loadGame(filename, num, 0);

}

char ConnectFour::Cell::getPosition() {
    return position;
}

void ConnectFour::Cell::setPosition(char letter) {
    position = letter;
}

void ConnectFour::setHeight(int num) {
    height = num;
}

void ConnectFour::setWidth(int num) {
    width = num;
}

void ConnectFour::setMoveLetter(char letter) {
    moveLetter = letter;
}

void ConnectFour::setPlayer(int num) {
    player = num;
}

void ConnectFour::setChoice(char ch) {
    choice = ch;
}

void ConnectFour::setTwoLetter() {
    twoLetter += 1;
}

void ConnectFour::setGameMode(char mode) {
    mode = tolower(mode);
    gameMode = mode;
    checkGameMode();
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

void ConnectFour::initializeBoard() {
    gameCells.resize(getWidth());

    for (int i = 0; i < getWidth(); ++i) {
        gameCells[i].resize(getHeight());

        for (int j = 0; j < getHeight(); ++j) {
            gameCells[i][j].setPosition('.');
        }
    }
}


void ConnectFour::printBoard() {
    // for letters
    for (char letter = 'a'; letter < 'a'+ getHeight(); ++letter)
        cout << letter << " ";
    cout << endl;
    // for squares
    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            cout << gameCells[i][j].getPosition() << " ";
        }
        cout << endl;
    }
}
// eger board da her yer dolar ve kimse kazanamazsa diye board u check eder
bool ConnectFour::checkFullBoard(int& lineLength){
    if(lineLength <= 1) {
        for (int i = 0; i < getHeight(); ++i) {
            setMoveLetter(i + 97);
            if (findLocation(lineLength) != -1)
                return false;
        }
        return true;
    }
    return false;
}

bool ConnectFour::operator >=( ConnectFour& other){
    if(getTwoLetter() >= other.getTwoLetter() )
        return true;
    return false;
}

// kazanan player in hamlesini check eder ve o hamleyi kucuk harflere cevirir
bool ConnectFour::winControl(char user){
    for (int i = 0; i < getWidth(); ++i) {
        for (int j = 0; j < getHeight(); ++j) {
            // yatay user1 - user2
            if( gameCells[i][j].getPosition() == user) {
                if (j+1 < getHeight() && gameCells[i][j + 1].getPosition() == user) {
                    if (j+2 < getHeight() && gameCells[i][j + 2].getPosition() == user) {
                        setTwoLetter();
                        if (j+3 < getHeight() && gameCells[i][j + 3].getPosition() == user) {
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                gameCells[i][j + k].setPosition(toLower(gameCells[i][j + k].getPosition()));   // kazanirsa harfleri kucuge cevirir.
                            printBoard();
                            return true;
                        }
                    }
                }
            }
            // dikey user1 - user2
            if( gameCells[i][j].getPosition() == user){
                if(i+1 < getWidth() && gameCells[i+1][j].getPosition() == user){
                    if( i+2 < getWidth() && gameCells[i+2][j].getPosition() == user){
                        setTwoLetter();
                        if(i+3 < getWidth() && gameCells[i+3][j].getPosition() == user){
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                gameCells[i + k][j].setPosition(toLower(gameCells[i + k][j].getPosition()));   // kazanirsa harfleri kucuge cevirir.
                            printBoard();
                            return true;
                        }
                    }
                }
            }
            // sag capraz user1 - user2
            if( gameCells[i][j].getPosition() == user){
                if(i-1 >= 0 && j+1 < getHeight() && gameCells[i-1][j+1].getPosition() == user){
                    if(i-2 >= 0 && j+2 < getHeight() && gameCells[i-2][j+2].getPosition() == user){
                        setTwoLetter();
                        if(i-3 >= 0 && j+3 < getHeight() && gameCells[i-3][j+3].getPosition() == user) {
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                gameCells[i - k][j + k].setPosition(toLower(gameCells[i - k][j + k].getPosition()));   // kazanirsa harfleri kucuge cevirir.
                            printBoard();
                            return true;
                        }
                    }
                }
            }
            // sol capraz user1 - user2
            if( gameCells[i][j].getPosition() == user){
                if(i-1 >= 0 && j+1 >= 0 && gameCells[i-1][j-1].getPosition() == user){
                    if(i-2 >= 0 && j+2 >= 0 && gameCells[i-2][j-2].getPosition() == user){
                        setTwoLetter();
                        if(i-3 >= 0 && j+3 >= 0 && gameCells[i-3][j-3].getPosition() == user) {
                            cout << endl << "FINAL BOARD !! " << endl;
                            cout << "-------------------------------------------------------------" << endl;
                            for (int k = 0; k < 4; ++k)
                                gameCells[i - k][j - k].setPosition(toLower(gameCells[i - k][j - k].getPosition()));   // kazanirsa harfleri kucuge cevirir.
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
    // yatay icin user1            // yatay icin user2
    if (winControl('X') == true || winControl('O') == true)
        return true;
    return false;
}
void ConnectFour::userMove(int& lineLength) {
    int error = 0, saveOrLoad, loadPlayer;
    string filename;
    bool control, loop = true;

    loadPlayer = player;

    while (loop) {
        control = true;
        // hamleyi al
        if(takeMove(error, filename, saveOrLoad, lineLength) == -1 )
            takeMove(error, filename, saveOrLoad, lineLength);

        if(saveOrLoad == 1) {
            if(saveGame(filename) == -1)
                cerr << "The game could not saved" << endl;
            else
                cout << "The game saved." << endl;
        }
        if(saveOrLoad == 2) {
            if(loadGame(filename, loadPlayer, lineLength) == -1)
                cerr << "The game could not loaded" << endl;
            else {
                cout << "Game loaded." << endl;
            }
            player = loadPlayer;
        }
        // konumu bul
        auto location = findLocation(lineLength);
        // hamleyi check et
        checkMove(error, location, control);
        if (gameCells[location][getMoveLetter() - 97].getPosition() == '.' && control == true)   // dogruysa donguden cik ve board u print et
        {
            loop = false;
            if (player == 1) {             // user1
                gameCells[location][getMoveLetter() - 97].setPosition('X');
                setLivingCell();
            }
            else if (player == 2) {       // user2
                gameCells[location][getMoveLetter() - 97].setPosition('O');
                setLivingCell();
            }
            cout << "User -> " << player << endl << endl;
            printBoard();
        }
    }
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

    if( line[0] < 97 || line[0] > 122) {
        cerr << "Please enter a letter" << endl;
        return -1;
    }

    lineLength = line.length();

    int k;
    for (k = 0; k < line.length(); ++k)
        line[k] = toLower(line[k]);

    if (line.length() > 1) {
        // if user entered wrong input
        size_t found = line.rfind(' ');
        if(found == string::npos){
            cerr << "You entered wrong input" << endl;
            return -1;
        }

        decltype(k) i, j;
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
    setMoveLetter(line[0]);
    setMoveLetter(toLower(getMoveLetter()));

    // if user entered wrong letter
    if (line.length() <= 1) {
        if (getMoveLetter() < 97 || getMoveLetter() >= 97 + getWidth())
            error = -1;                            // board size i disinda letter girerse
    }
}
// sutunda bos olan yeri return eder. Doluysa -1 return eder
int ConnectFour::findLocation(int lineLength){
    if(lineLength <= 1) {
        for (int i = getWidth() - 1; i >= 0; i--) {
            if (gameCells[i][getMoveLetter() - 97].getPosition() == '.')
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
            userMove(lineLength);
            // win funct
            if(win() == true) {
                cout << endl  <<"USER "<< player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            setPlayer(player2);
            userMove(lineLength);
            // win
            if(win() == true) {
                cout << endl << "USER "<< player2 << " WON!!" << endl;         // user2 kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            if(checkFullBoard(lineLength) == true){
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
            userMove(lineLength);
            // win funct
            if (win() == true) {
                cout << endl << "USER " << player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            computerMove();
            // win
            if (win() == true) {
                cout << endl << "COMPUTER WON!!" << endl;                       // computer kazanir ve oyun biter
                cout << endl  << "Living Cell: " << getLivingCell() << endl << endl;
                game = true;
                return 1;
            }
            cout << "-------------------------------------------------------------" << endl;
            if (checkFullBoard(lineLength) == true) {
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
            if (gameCells[i][j].getPosition() == 'X') {
                // dikey icin
                if (i-1 >= 0 && gameCells[i - 1][j].getPosition() == 'X'){
                    if(i-2 >= 0 && gameCells[i - 2][j].getPosition() == '.') {
                        gameCells[i - 2][j].setPosition('O');
                        setLivingCell();
                        return 1;
                    }
                }
                    // yatay icin
                else if (j+1 < getHeight() && gameCells[i][j + 1].getPosition() == 'X') {
                    if (j+2 < getHeight() && gameCells[i][j + 2].getPosition() == '.') {
                        if (i+1 < getWidth() && j+2 < getHeight() && gameCells[i + 1][j + 2].getPosition() != '.') {
                            gameCells[i][j + 2].setPosition('O');
                            setLivingCell();
                            return 1;
                        } else if (j-1 >= 0 && gameCells[i][j - 1].getPosition() == '.' && gameCells[i + 1][j - 1].getPosition() != '.') {
                            gameCells[i][j - 1].setPosition('O');
                            setLivingCell();
                            return 1;
                        }
                    }
                }
                    // sag capraz icin
                else if (i-1 >= 0 && j+1 < getHeight() && gameCells[i - 1][j + 1].getPosition() == 'X') {
                    if (i-2 >= 0 && j+2 < getHeight() && gameCells[i - 2][j + 2].getPosition() == '.') {
                        if (i-1 >= 0 && j+2 < getHeight() && gameCells[i - 1][j + 2].getPosition() != '.') {
                            gameCells[i - 2][j + 2].setPosition('O');
                            setLivingCell();
                            return 1;
                        } else if (i+1 < getWidth() && j-1 >= 0 && gameCells[i + 1][j - 1].getPosition() == '.' && gameCells[i + 2][j - 1].getPosition() != '.') {
                            gameCells[i + 1][j - 1].setPosition('O');
                            setLivingCell();
                            return 1;
                        }
                    }
                }
                    // sol capraz icin
                else if (i-1 >= 0 && j-1 >= 0 && gameCells[i - 1][j - 1].getPosition() == 'X'){
                    if(i-2 >= 0 && j-2 >= 0 && gameCells[i - 2][j - 2].getPosition() == '.') {
                        if (i-1 >= 0 && j-2 >= 0 && gameCells[i - 1][j - 2].getPosition() != '.') {
                            gameCells[i - 2][j - 2].setPosition('O');
                            setLivingCell();
                            return 1;
                        } else if (i+1 < getWidth() && j+1 < getHeight() && gameCells[i + 1][j + 1].getPosition() == '.' && gameCells[i + 2][j + 1].getPosition() != '.') {
                            gameCells[i + 1][j + 1].setPosition('O');
                            setLivingCell();
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return result;
}
void ConnectFour::firstComputerMove(){
    gameCells[getWidth()-1][getHeight()/2].setPosition('O');
    setLivingCell();

    if( gameCells[getWidth()-1][getHeight()/2].getPosition() == 'X' ) {
        gameCells[getWidth() - 1][getHeight() / 2 + 1].setPosition('O');
        setLivingCell();
    }
}
int ConnectFour::computerMove() {
    int result = 0;
    // board u check eder ve ilk hamle yapilmissa hic döngüye girmeden devam eder
    if(count == 0) {
        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                if (gameCells[i][j].getPosition() == 'O')
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
                    if (gameCells[i][j].getPosition() == 'O') {
                        // sag yatay icin
                        if (j + 1 < getHeight() && gameCells[i][j + 1].getPosition() == '.') {
                            if (getWidth() >= i + 1 ) {
                                gameCells[i][j + 1].setPosition('O');
                                setLivingCell();

                            } else if (gameCells[i + 1][j + 1].getPosition() != '.') {
                                gameCells[i][j + 1].setPosition('O');
                                setLivingCell();
                            }
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;       // loop tan cikabilsin diye
                        }
                        // sol yatay icin
                        if (j - 1 >= 0 && gameCells[i][j - 1].getPosition() == '.') {
                            if (getWidth() >= i + 1) {
                                gameCells[i][j - 1].setPosition('O');
                                setLivingCell();
                            } else if (gameCells[i + 1][j - 1].getPosition() != '.') {
                                gameCells[i][j - 1].setPosition('O');
                                setLivingCell();
                            }
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;       // loop tan cikabilsin diye
                        }
                    }
                    // dikey icin
                    if (gameCells[i][j].getPosition() == 'O'){
                        if(i - 1 >= 0 && gameCells[i - 1][j].getPosition() == '.'){
                            gameCells[i - 1][j].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                    }
                    // sag capraz icin
                    if (gameCells[i][j].getPosition() == 'O'){
                        // sag yukari capraz
                            if( j - 1 >= 0 && i + 1 < getWidth() && gameCells[i + 1][j - 1].getPosition() == '.'){

                            gameCells[i + 1][j - 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                    }
                    // sol capraz icin
                    if (gameCells[i][j].getPosition() == 'O'){
                        if(i+1 < getWidth() && j-1 >= 0 && i+2 < getWidth() && gameCells[i + 1][j - 1].getPosition() == '.'
                           ){

                            gameCells[i + 1][j - 1].setPosition('O');
                            setLivingCell();
                            cout << "Computer ->" << endl << endl;
                            printBoard();
                            return 1;
                        }
                        if(i+1 < getWidth() && j-1 >= 0 && j+1 < getHeight() && i+2 < getWidth()
                           && gameCells[i + 1][j + 1].getPosition() == '.' ){

                            gameCells[i + 1][j + 1].setPosition('O');
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

// This function tests height/width of board
int ConnectFour::testBoardSize(int num) {
    if(num < 4){
        cout << "Board width/height is not smaller than 4" << endl;
        return -1;
    }
    else if( num > 32 ){
        cout << "Board width/height is not bigger than 32" << endl;
        return -1;
    }
    return 1;
}
void ConnectFour::selectGameMode(){
    char mode;
    cout << "Please select a game mode" << endl;
    cin >> mode;
    setGameMode(mode);
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

int ConnectFour::saveGame(string fileName) {
    ofstream file;
    file.open(fileName);
    if(file.is_open()) {
        file << getChoice() << " ";
        file << getPlayer() << " ";
        file << getHeight() << " ";
        file << getWidth();

        for (int i = 0; i < getHeight(); ++i) {
            for (int j = 0; j < getWidth(); ++j)
                file << gameCells[i][j].getPosition() << " ";
            file << endl;
        }
    }
    else
        return -1;
    file.close();
}

int ConnectFour::loadGame(string fileName, int& loadPlayer, int lineLength){
    int player, sizeH, sizeW;
    char data;
    char ch;
    ifstream file;
    file.open(fileName);
    if(file.is_open()){
        if ( file.peek() == ifstream::traits_type::eof() )
        {
            cerr << "File is empty" << endl;
            return -1;
        }

        file >> ch;
        setChoice(ch);

        file >> player;
        setPlayer(player);

        file >> sizeH;
        gameCells.resize(sizeH);        // board u yeni board a gore resize eder
        setHeight(sizeH);

        file >> sizeW;
        for (int k = 0; k < sizeH; ++k) {
            gameCells[k].resize(sizeW);
        }
        setWidth(sizeW);

        for (int i = 0; i < getWidth(); ++i) {
            for (int j = 0; j < getHeight(); ++j) {
                file >> data;
                gameCells[i][j].setPosition(data);
            }
        }
        printBoard();
        for (int l = 0; l < getWidth(); ++l) {
            for (int i = 0; i < getHeight(); ++i) {
                if(gameCells[l][i].getPosition() == 'X' || gameCells[l][i].getPosition() == 'O')
                    setLivingCell();
            }
        }
        cout << "Living Cell: " << getLivingCell() << endl << endl;

        cout << "Player " << getPlayer() << endl;
        loadPlayer = getPlayer();

        if(getChoice() == 'c')
            playGame();
        else{
            if(getPlayer() == 2){
                // 2.oyuncuysa ilk hamleyi yapar sonra diger fonk da devam eder.
                userMove(lineLength);
                // win funct
                if (win() == true) {
                    cout << endl << "USER " << getPlayer() << " WON!!" << endl;     // user2 kazanir ve oyun biter
                    exit(1);
                }
                cout << "-------------------------------------------------------------" << endl;
            }
            playGame();
        }
    }
    else
        return -1;
}

char ConnectFour::toLower(char letter) {
    if(letter > 64 && letter < 91)
        letter = letter + 32;
    return letter;
}


// User selects the game.
void ConnectFour::selectGame(){
    char choice;
    cout << "Please select a game." << endl;
    cout << "Player | Computer | Exit " << endl;
    cin >> choice;
    setChoice(tolower(choice));

    if(getChoice() != 'p' && getChoice() != 'c' && getChoice() != 'e') {
        cerr << "Please try again." << endl;
        selectGame();
    }
}