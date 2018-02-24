//
// Created by derya on 22.11.2017.
//

#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H


#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"

namespace Zeytin {

    class ConnectFourPlusUndo : public ConnectFourPlus {
    public:
        void undoMove();

        void play(int &lineLength) final;

        int playGame() final;
    };
}

#endif //CONNECTFOURPLUSUNDO_H
