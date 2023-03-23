#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "card.hpp"
#include <string>
#include <vector>

class Game {
    private:
        Player p1;
        Player p2;
        std::vector<std::string> logVector; // add the played log
        unsigned int nbrTotalDraw = 0;

    public:
        Game(Player player1, Player player2);
        void playTurn();
        void playAll();
        void printLastTurn();
        void printLog();
        void printStats();

};

#endif // GAME_HPP
