//
// Created by derya on 22.11.2017.
//

#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"

namespace Zeytin {

    class ConnectFourDiag : public ConnectFourAbstract {
    public:
        ConnectFourDiag() = default;

        int diagMove();

        bool winControl(char user) final;

        int blockX() final;

        int play() final;

        void play(int &lineLength) final;

        int startGame() final;

        int loadGame(string fileName, int &loadPlayer, int lineLength) final;

        int playGame() final;
    };
}

#endif //CONNECTFOURDIAG_H
