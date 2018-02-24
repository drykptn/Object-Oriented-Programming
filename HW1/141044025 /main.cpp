#include <iostream>
const int boardSize = 20;

using namespace std;

void getBoardSize(int& size );
bool checkBoardSize(const int size);
void initializeBoard(const int size, char board[][boardSize]);
char toLower(char letter);
void selectGame(char& choice);
void printBoard(char board[][boardSize], const int size);
void takeMove(char& letter, int& error, const int size);
int findLocation(char letter, char board[][boardSize], const int size);
void checkMove(const int error, const int location, bool& control);
void userMove(char board[][boardSize], const int size,const int player);
bool checkFullBoard(char board[][boardSize], const int size);
bool winControl(char board[][boardSize], const int size, char user);
int blockX(char board[][boardSize], int size);
void firstComputerMove(char board[][boardSize], const int size);
int computerMove(char board[][boardSize], const int size, int& count);
bool playGame(char board[][boardSize],const int size, char choice);


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
bool checkBoardSize(const int size){
    // If size is between 0 and 20 and it's divided by 2, it s true.
    if( size >= 4 && size <= 20 && size % 2 == 0)
        return true;
    else{
        cout << "Please check your board size!" << endl;
        return false;
    }
}
// board u initialize eder
void initializeBoard(const int size, char board[][boardSize]) {
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
    if(choice != 'p' && choice != 'c' && choice != 'e')
        cerr << "Please try again." << endl;
}
// board u print eder
void printBoard(char board[][boardSize], const int size){
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
void takeMove(char& letter, int& error, const int size){
    error = 0;
    cout << "Enter your move" << endl;
    cin >> letter;
    letter = toLower(letter);

    // if user entered wrong letter
    if(letter < 97 || letter > 97+size )  // board size i disinda letter girerse
        error = -1;
}// sutunda bos olan yeri return eder. Doluysa -1 return eder
int findLocation(char letter, char board[][boardSize], const int size){
    for (int i = size-1; i >= 0; i--) {
        if( board[i][letter-97] == '.')
            return i;
    }
    return -1;
}// user yanlis harf/value girerse ya da hamle yapacagi sutun doluysa uyari verir.
void checkMove(const int error, const int location, bool& control){
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
void userMove(char board[][boardSize], const int size,const int player) {
    int error = 0;
    char letter;
    bool control, loop = true;

    while (loop) {
        control = true;
        // hamleyi al
        takeMove(letter, error, size);
        // konumu bul
        int location = findLocation(letter, board, size);
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
}// eger board da her yer dolar ve kimse kazanamazsa diye board u check eder
bool checkFullBoard(char board[][boardSize], const int size){
    for (int i = 0; i < size; ++i) {
        if(findLocation(i + 97, board, size) != -1 )
            return false;
    }
    return true;
}// kazanan player in hamlesini check eder ve o hamleyi kucuk harflere cevirir
bool winControl(char board[][boardSize], const int size, char user){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
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
int blockX(char board[][boardSize], int size) {
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
void firstComputerMove(char board[][boardSize], const int size){
    board[size-1][size/2] = 'O';
    if(board[size-1][size/2] == 'X')
        board[size-1][size/2+1] = 'O';
    cout << "Computer ->" << endl << endl;
    printBoard(board, size);
}
int computerMove(char board[][boardSize], const int size, int& count) {
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
bool playGame(char board[][boardSize],const int size, char choice) {
    const int player1 = 1, player2 = 2;
    int user = 'p', computer = 'c', count = 0;
    // user-user
    if (choice == user) {
        while(true) {
            userMove(board, size, player1);
            // win funct
            if(win(board, size) == true) {
                cout << endl  <<"USER "<< player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                return false;
            }
            cout << "-------------------------------------------------------------" << endl;
            userMove(board, size, player2);
            // win
            if(win(board, size) == true) {
                cout << endl << "USER "<< player2 << " WON!!" << endl;         // user2 kazanir ve oyun biter
                return false;
            }
            cout << "-------------------------------------------------------------" << endl;
            if(checkFullBoard(board, size) == true){
                cerr << "There is no empty space on the board." << endl;
                return false;
            }

        }
    }
    // user-computer
    else if (choice == computer) {
        while(true) {
            userMove(board, size, player1);
            // win funct
            if(win(board, size) == true) {
                cout << endl << "USER "<< player1 << " WON!!" << endl;          // user1 kazanir ve oyun biter
                return false;
            }
            cout << "-------------------------------------------------------------" << endl;
            computerMove(board, size, count);
            // win
            if(win(board, size) == true) {
                cout << endl << "COMPUTER WON!!" << endl;                       // computer kazanir ve oyun biter
                return false;
            }
            cout << "-------------------------------------------------------------" << endl;
            if(checkFullBoard(board, size) == true){
                cerr << "There is no empty space on the board." << endl;
                return false;
            }
        }
    }
}
