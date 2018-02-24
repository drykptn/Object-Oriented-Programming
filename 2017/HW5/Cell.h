/*
In this homework, you will write a hierarchy of ConnectFour classes. But first, there should be
cell class (no inner class) a Connect Four cell. The class Cell will hold the position of the cell (A,
B, C, etc) and the row number (1, 2, 3, etc). This class will also include all necessary setters/getters,
constructors etc. Remember a cell can be empty, user (user1, user2) or computer.
Your base class ConnectFourAbstract will define the following member functions. It will be
an abstract base class.
• The class will have functions to read and write from files. You will decide on the file format.
• The class will have functions to return the current width and height of the board
• The class will have a function that displays the current board on the screen
• The class will have two functions named play that plays the game for a single time step. First
function does not take a parameter and it plays the computer. The second function takes a cell
position and it plays the user.
• The class should have a function that returns if the game ended.
• The class should have a function named playGame. This function plays the game by asking
the user the board size first then asks the user to play and the computer plays, etc.
The class ConnectFourPlus will derive from the abstract class. It will play very similar to regular
Connect Four but it will only accept horizontally or vertically connected cells as the goal of the game.
Similarly, the class ConnectFourDiag will derive from the abstract class. It will play very similar
to regular Connect Four but it will only accept diagonally connected cells as the goal of the game.
The class ConnectFourPlusUndo will be very similar to ConnectFourPlus. It can undo the
moves of the user or the computer until the beginning of the game.
*/
//
// Created by derya on 22.11.2017.
//

#ifndef CELL_H
#define CELL_H

#include <string>

namespace Zeytin {

    class Cell {
    public:
        Cell() {}        // default constructor

        // setter function
        void setPosition(char letter) {
            position = letter;
        }

        // getter functions
        char getPosition() const { return position; }

    private:
        int row;        // 1,2,3..
        char position;   // A,B,C..
    };

}
#endif //CELL_H
