/*
You will continue developing your Connect Four program with this homework. You will add the
following features to your program.
• Your program should accept commands for loading and saving the game board. For example,
instead of giving the column letters, if the user enters the command
LOAD FILE.TXT
your program loads the game board from this file. Similarly, if the user enters the command
SAVE FILE.TXT
your program saves the current game status to this file. You should save and load all game
related information such as user vs user or computer, board size etc.
• Your program should have at least one function that takes a parameter by reference and a
constant parameter by reference.
• Your program should have at least one function that uses default arguments.
• Your program should have at least one auto statement and one declrtype statement.
• All the errors should be printed to cerr object and all the other text should be sent to cout .
The rest of the program will be the same as HW1.
*/
#include <iostream>
#include <fstream>
#include <string.h>

const int boardSize = 20;

using namespace std;

void getBoardSize(int& size );
bool checkBoardSize(const int& size);
void initializeBoard(const int& size, char board[][boardSize]);
char toLower(char letter);
void selectGame(char& choice);
void printBoard(char board[][boardSize], const int& size);
int takeMove(char& letter, int& error, const int& size, string& filename, int& saveOrLoad, int& lineLength);
int findLocation(char letter, char board[][boardSize], const int size, int lineLength);
void checkMove(const int& error, const int& location, bool& control);
char userMove(char board[][boardSize], int& size,int player, int& lineLength, char choice);
bool checkFullBoard(char board[][boardSize], int& size, int& lineLength);
bool winControl(char board[][boardSize], const int size, char user);
int blockX(char board[][boardSize], const int& size);
void firstComputerMove(char board[][boardSize], const int& size);
int computerMove(char board[][boardSize], const int& size, int& count);
bool playGame(char board[][boardSize],const int size, char choice);
int saveGame(char board[][boardSize], const int size, int player, string fileName, char choice);
int loadGame(char board[][boardSize], int& size, string fileName, int& loadPlayer, int& lineLength, char& choice);
bool win(char board[][boardSize], const int size);

int main() {
    char board[boardSize][boardSize], choice;
    int size = 0;

    getBoardSize(size);

    if (checkBoardSize(size) != false) {
        initializeBoard(size, board);
        selectGame(choice);
        printBoard(board, size);
        playGame(board, size, choice);
    }
    return 0;
}

// user dan board un size ini alir
void getBoardSize(int& size ){
    cout << "Please enter a board size : " << endl;
    cin >> size;
}
// It checks the size of board.
bool checkBoardSize(const int& size){
    // If size is between 0 and 20 and it's divided by 2, it s true.
    if( size >= 4 && size <= 20 && size % 2 == 0)
        return true;
    else{
        cout << "Please check your board size!" << endl;
        return false;
    }
}
// board u initialize eder
void initializeBoard(const int& size, char board[][boardSize]) {
    // initial board
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j)
            board[i][j] = '.';
    }
}
// The function is convert to lower
char toLower(char letter){
    if(letter > 64 && letter < 91)
        letter = letter + 32;
    return letter;
}
// User selects the game.
void selectGame(char& choice){
    cout << "Please select a game." << endl;
    cout << "1. User - User -> P" << endl;
    cout << "2. User - Computer -> C" << endl;
    cout << "3. Exit -> E" << endl;
    cin >> choice;
    choice = tolower(choice);
    if(choice != 'p' && choice != 'c' && choice != 'e') {
        cerr << "Please try again." << endl;
        selectGame(choice);
    }
}
// board u print eder
void printBoard(char board[][boardSize], const int& size){
    // for letters
    for (char letter = 'a'; letter < 'a'+ size; ++letter)
        cout << letter << " ";
    cout << endl;
    // for squares
    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col)
            cout << board[row][col] << " ";
        cout << endl;
    }
}
// It takes input from user
int takeMove(char& letter, int& error, const int& size, string& filename, int& saveOrLoad, int& lineLength) {
    char temp1[10], temp2[10];
    error = 0;
    string line, temp;
    cout << "Enter your move" << endl;

    getline(cin, line);
    // bir tane fazladan bos karakter aliyor. Onu engellemek icin 2 defa getline kullanildi
    while (line.length() == 0)
        getline(cin, line);

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
    letter = line[0];
    letter = toLower(letter);

    // if user entered wrong letter
    if (line.length() <= 1) {
        if (letter < 97 || letter >= 97 + size)
            error = -1;                            // board size i disinda letter girerse
    }
}
// sutunda bos olan yeri return eder. Doluysa -1 return eder
int findLocation(char letter, char board[][boardSize], const int size, const int lineLength){
    if(lineLength <= 1) {
        for (int i = size - 1; i >= 0; i--) {
            if (board[i][letter - 97] == '.')
                return i;
        }
        return -1;
    }
    return 2;
}// user yanlis harf/value girerse ya da hamle yapacagi sutun doluysa uyari verir.
void checkMove(const int& error, const int& location, bool& control){
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
// gelen hamleyi uygular check eder ve yanlislik varsa false return eder.
char userMove(char board[][boardSize], int& size, int player, int& lineLength, char choice) {
    int error = 0, saveOrLoad, loadPlayer;
    char letter;
    string filename;
    bool control, loop = true;

    loadPlayer = player;

    while (loop) {
        control = true;
        // hamleyi al
        takeMove(letter, error, size, filename, saveOrLoad, lineLength);
        if(saveOrLoad == 1) {
            if(saveGame(board, size, player, filename, choice) == -1)
                cerr << "The game could not saved" << endl;
            else
                cout << "The game saved." << endl;
        }
        if(saveOrLoad == 2) {
            if(loadGame(board, size, filename, loadPlayer, lineLength, choice) == -1)
                cerr << "The game could not loaded" << endl;
            else {
                cout << "Game loaded." << endl;
            }
            player = loadPlayer;
        }
        // konumu bul
        auto location = findLocation(letter, board, size, lineLength);
        // hamleyi check et
        checkMove(error, location, control);
        if (board[location][letter - 97] == '.' && control == true)   // dogruysa donguden cik ve board u print et
        {
            loop = false;
            if (player == 1)             // user1
                board[location][letter - 97] = 'X';
            else if (player == 2)        // user2
                board[location][letter - 97] = 'O';
            cout << "User -> " << player << endl << endl;
            printBoard(board, size);
        }
    }
    return choice;
}
// eger board da her yer dolar ve kimse kazanamazsa diye board u check eder
bool checkFullBoard(char board[][boardSize], int& size, int& lineLength){
    if(lineLength <= 1) {
        for (int i = 0; i < size; ++i) {
            if (findLocation(i + 97, board, size, lineLength) != -1)
                return false;
        }
        return true;
    }
    return false;
}
// kazanan player in hamlesini check eder ve o hamleyi kucuk harflere cevirir
bool winControl(char board[][boardSize], const int size, char user){
    for (auto i = 0; i < size; ++i) {
        for (auto j = 0; j < size; ++j) {
            // yatay user1 - user2
            if( board[i][j] == user) {
                if (board[i][j + 1] == user) {
                    if (board[i][j + 2] == user) {
                        if (board[i][j + 3] == user) {
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                board[i][j + k] = toLower(board[i][j + k]);   // kazanirsa harfleri kucuge cevirir.
                            printBoard(board, size);
                            return true;
                        }
                    }
                }
            }
            // dikey user1 - user2
            if( board[i][j] == user){
                if( board[i+1][j] == user){
                    if( board[i+2][j] == user){
                        if( board[i+3][j] == user) {
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                board[i + k][j] = toLower(board[i + k][j]);   // kazanirsa harfleri kucuge cevirir.
                            printBoard(board, size);
                            return true;
                        }
                    }
                }
            }
            // sag capraz user1 - user2
            if( board[i][j] == user){
                if( board[i-1][j+1] == user){
                    if( board[i-2][j+2] == user){
                        if( board[i-3][j+3] == user) {
                            cout << "-------------------------------------------------------------" << endl;
                            cout << endl << "FINAL BOARD !! " << endl;
                            for (int k = 0; k < 4 ; ++k)
                                board[i - k][j + k] = toLower(board[i - k][j + k]);   // kazanirsa harfleri kucuge cevirir.
                            printBoard(board, size);
                            return true;
                        }
                    }
                }
            }
            // sol capraz user1 - user2
            if( board[i][j] == user){
                if( board[i-1][j-1] == user){
                    if( board[i-2][j-2] == user){
                        if( board[i-3][j-3] == user) {
                            cout << endl << "FINAL BOARD !! " << endl;
                            cout << "-------------------------------------------------------------" << endl;
                            for (int k = 0; k < 4; ++k)
                                board[i - k][j - k] = toLower(
                                        board[i - k][j - k]);   // kazanirsa harfleri kucuge cevirir.
                            printBoard(board, size);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool win(char board[][boardSize], const int size){
    // yatay icin user1                         // yatay icin user2
    if (winControl(board, size, 'X') == true || winControl(board, size, 'O') == true)
        return true;
    return false;
} // Computer once user1 ( X ) e bakar engellenebilecek hamlesi varsa engeller
int blockX(char board[][boardSize], const int& size) {
    int result = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (board[i][j] == 'X') {
                // dikey icin
                if (board[i - 1][j] == 'X'){
                    if(board[i - 2][j] == '.') {
                        board[i - 2][j] = 'O';
                        return 1;
                    }
                }
                    // yatay icin
                else if (board[i][j + 1] == 'X') {
                    if (board[i][j + 2] == '.') {
                        if (board[i + 1][j + 2] != '.') {
                            board[i][j + 2] = 'O';
                            return 1;
                        } else if (board[i][j - 1] == '.' && board[i + 1][j - 1] != '.') {
                            board[i][j - 1] = 'O';
                            return 1;
                        }
                    }
                }
                    // sag capraz icin
                else if (board[i - 1][j + 1] == 'X') {
                    if (board[i - 2][j + 2] == '.') {
                        if (board[i - 1][j + 2] != '.') {
                            board[i - 2][j + 2] = 'O';
                            return 1;
                        } else if (board[i + 1][j - 1] == '.' && board[i + 2][j - 1] != '.') {
                            board[i + 1][j - 1] = 'O';
                            return 1;
                        }
                    }
                }
                    // sol capraz icin
                else if (board[i - 1][j - 1] == 'X'){
                    if(board[i - 2][j - 2] == '.') {
                        if (board[i - 1][j - 2] != '.') {
                            board[i - 2][j - 2] = 'O';
                            return 1;
                        } else if (board[i + 1][j + 1] == '.' && board[i + 2][j + 1] != '.') {
                            board[i + 1][j + 1] = 'O';
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return result;
}// computer ilk hamlesini yapar.
void firstComputerMove(char board[][boardSize], const int& size){
    board[size-1][size/2] = 'O';
    if(board[size-1][size/2] == 'X')
        board[size-1][size/2+1] = 'O';
}
int computerMove(char board[][boardSize], const int& size, int& count) {
    int result = 0;
    // board u check eder ve ilk hamle yapilmissa hic döngüye girmeden devam eder
    if(count == 0) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == 'O')
                    count += 1;
            }
        }
    }
    // eger ilk hamle yapilmamissa yapar
    if (count == 0 )
        firstComputerMove(board, size);
    else {
        // once user1 i engellemeye calisir
        result = blockX(board, size);
        // engellenecek hamle yoksa kendi kazanmaya calisir
        if(result == 0) {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    // yatay icin
                    if (board[i][j] == 'O'){
                        if(board[i][j + 1] == '.' && board[i + 1][j + 1] != '.'){
                            board[i][j + 1] = 'O';
                            i = size + 1;       // loop tan cikabilsin diye
                        }
                        if(board[i][j + 1] != '.' && board[i][j - 1] == '.' && board[i + 1][j - 1] != '.'){
                            board[i][j - 1] = 'O';
                            i = size + 1;
                        }
                    }
                    // dikey icin
                    if (board[i][j] == 'O'){
                        if(board[i - 1][j] == '.'){
                            board[i - 1][j] = 'O';
                            i = size + 1;
                        }
                    }
                    // sag capraz icin
                    if (board[i][j] == 'O'){
                        if(board[i - 1][j + 1] == '.' && board[i][j + 1] != '.'){
                            board[i - 1][j + 1] = 'O';
                            i = size + 1;
                        }
                        if(board[i - 1][j + 1] != '.' && board[i + 1][j - 1] == '.' && board[i + 2][j - 1] != '.'){
                            board[i + 1][j - 1] = 'O';
                            i = size + 1;
                        }
                    }
                    // sol capraz icin
                    if (board[i][j] == 'O'){
                        if(board[i + 1][j - 1] == '.' && board[i + 2][j - 1] != '.'){
                            board[i + 1][j - 1] = 'O';
                            i = size + 1;
                        }
                        if(board[i + 1][j - 1] != '.' && board[i + 1][j + 1] == '.' && board[i + 2][j + 1] != '.'){
                            board[i + 1][j + 1] = 'O';
                            i = size + 1;
                        }
                    }
                }
            }
        }
    }
    if(result > 0) {
        cout << "Computer ->" << endl << endl;
        printBoard(board, size);
        return 0;
    }
    cout << "Computer ->" << endl << endl;
    printBoard(board, size);
    return 1;

}

bool playGame(char board[][boardSize], int size, char choice) {
    const int player1 = 1, player2 = 2;
    int user = 'p', computer = 'c', count = 0, lineLength;
    // user-user
    if (choice == user) {
        while(true) {
            userMove(board, size, player1, lineLength, choice);
            // win funct
            if(win(board, size) == true) {
                cout << endl  <<"USER "<< player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                exit(1);
            }
            cout << "-------------------------------------------------------------" << endl;
            userMove(board, size, player2, lineLength, choice);
            // win
            if(win(board, size) == true) {
                cout << endl << "USER "<< player2 << " WON!!" << endl;         // user2 kazanir ve oyun biter
                exit(1);
            }
            cout << "-------------------------------------------------------------" << endl;
            if(checkFullBoard(board, size, lineLength) == true){
                cerr << "There is no empty space on the board." << endl;
                exit(1);
            }
        }
    }
        // user-computer
    else if (choice == computer) {
        while(true) {
            userMove(board, size, player1, lineLength, choice);
            // win funct
            if (win(board, size) == true) {
                cout << endl << "USER " << player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                exit(1);
            }
            cout << "-------------------------------------------------------------" << endl;
            computerMove(board, size, count);
            // win
            if (win(board, size) == true) {
                cout << endl << "COMPUTER WON!!" << endl;                       // computer kazanir ve oyun biter
                exit(1);
            }
            cout << "-------------------------------------------------------------" << endl;
            if (checkFullBoard(board, size, lineLength) == true) {
                cerr << "There is no empty space on the board." << endl;
                exit(1);
            }


        }
    }
}

int saveGame(char board[][boardSize], const int size, int player, string fileName, char choice){
    ofstream file;
    file.open(fileName);
    if(file.is_open()) {
        file << choice << " ";
        file << player << " ";
        file << size;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j)
                file << board[i][j] << " ";
            file << endl;
        }
    }
    else
        return -1;
    file.close();
}

int loadGame(char board[][boardSize], int& size, string fileName, int& loadPlayer, int& lineLength, char& choice){
    int player;
    char data;
    ifstream file;
    file.open(fileName);
    if(file.is_open()){
        if ( file.peek() == ifstream::traits_type::eof() )
        {
            cerr << "File is empty" << endl;
            return -1;
        }
        file >> choice;
        file >> player;
        file >> size;

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> data;
                board[i][j] = data;
            }
        }
        printBoard(board, size);

        cout << "Player " << player << endl;
        loadPlayer = player;

        if(choice == 'c')
            playGame(board, size, choice);
        else{
            if(player == 2){
                // 2.oyuncuysa ilk hamleyi yapar sonra diger fonk da devam eder.
                userMove(board, size, player, lineLength, choice);
                // win funct
                if (win(board, size) == true) {
                    cout << endl << "USER " << player << " WON!!" << endl;     // user2 kazanir ve oyun biter
                    exit(1);
                }
                cout << "-------------------------------------------------------------" << endl;
            }
            playGame(board, size, choice);
        }
    }
    else
        return -1;
}
