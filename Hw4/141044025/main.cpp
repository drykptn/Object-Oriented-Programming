#include "ConnectFour.h"

int main(int argc, char* argv[]) {
    ConnectFour cf;
    cf.selectGameMode();

    if(cf.getGameMode() == 's') {
        cf.startGame();
        cf.playGame();
    }
    else if(cf.getGameMode() == 'm') {
        // multiple secim icin her objeye game modu set edilir
        ConnectFour object1(cf.getGameMode()), object2(cf.getGameMode()), object3(cf.getGameMode()),
                object4(cf.getGameMode()), object5(cf.getGameMode());

        cout << "Object 1" << endl;
        object1.startGame();
        cout << "Object 2" << endl;
        object2.startGame();

        cout << "Object 3" << endl;
        object3.startGame();
        cout << "Object 4" << endl;
        object4.startGame();
        cout << "Object 5" << endl;
        object5.startGame();

        int obj;
        int count = 0;

        while(count < 5) {
            cout << "Choose an object: 1/2/3/4/5" << endl;
            cin >> obj;
            if (obj == 1) {
                if(object1.getGame())
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object1.playGame();

                    if (object1.getGame())
                        count += 1;
                }
            } else if (obj == 2) {
                if(object2.getGame())
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object2.playGame();
                    if (object2.getGame())
                        count += 1;
                }
            } else if (obj == 3) {
                if(object3.getGame())
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object3.playGame();
                    if (object3.getGame())
                        count += 1;
                }
            } else if (obj == 4) {
                if(object4.getGame())
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object4.playGame();
                    if (object4.getGame())
                        count += 1;
                }
            } else if (obj == 5) {
                if(object5.getGame())
                    cerr << "The game is over. Please choice other ones. " << endl;
                else {
                    object5.playGame();
                    if (object5.getGame())
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