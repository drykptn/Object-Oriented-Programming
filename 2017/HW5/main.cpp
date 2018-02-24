
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace std;


    int main(int argc, char *argv[]) {
        char gameMode;
        cout << "Please enter a class name" << endl;
        cin >> gameMode;

        if ('p' == tolower(gameMode)) {
            Zeytin::ConnectFourPlus cp;
            cp.playGame();
        }
        if ('d' == tolower(gameMode)) {
            Zeytin::ConnectFourDiag cd;
            cd.playGame();
        }
        if ('u' == tolower(gameMode)) {
            Zeytin::ConnectFourPlusUndo cu;
            cu.playGame();
        }
        return 0;
    }