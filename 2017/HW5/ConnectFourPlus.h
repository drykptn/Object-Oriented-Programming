//
// Created by derya on 22.11.2017.
//

#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include "ConnectFourAbstract.h"

namespace Zeytin {

    class ConnectFourPlus : public ConnectFourAbstract {
    public:
        ConnectFourPlus() = default;

        int plusMove();

        void play(int &lineLength) override;

        int playGame() override;

        bool winControl(char user) final;

        int play() final;

        int blockX() final;

        int startGame() final;

        int loadGame(string fileName, int &loadPlayer, int lineLength) final;
    };
}

#endif //CONNECTFOURPLUS_H
