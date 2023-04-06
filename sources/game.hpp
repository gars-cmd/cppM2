#ifndef GAME_HPP
#define GAME_HPP

#include "player.hpp"
#include "card.hpp"
#include <cstdint>
#include <string>
#include <vector>
namespace ariel {


class Game {
    private:
        Player* p1;
        Player* p2;
        std::vector<std::string> logVector; // add the played log
        unsigned int nbrTotalDraw = 0;

    public:
    enum Result {
        P1_WIN,
        P2_WIN,
        DRAW
    };
        Game(Player player1, Player player2);
        void playTurn();
        Player& getPlayer1();
        Player& getPlayer2();
        void playAll();
        void printLastTurn();
        std::vector<std::string> getLogVector();
        unsigned int getNbrTotalDraw();
        Result find_winner(Card p1_card, Card p2_card);
        void add_log( std::string previous_string, Player winner, Player looser , ariel::Card p1_card, ariel::Card p2_card);
        void handleTeko(ariel::Card card_p1, ariel::Card card_p2);
        void handlerWinner(Result result, ariel::Card card_p1, ariel::Card card_p2, std::string string);
        void printLog();
        void printWiner();
        void printStats();
        std::vector<Card*> generateCardStack(); //create a new card stack of 52 cards
        void shuffleStack(std::vector<Card*>& cardStack); //function that shuffle the cardStack
        void initTheWar();

};

}
#endif // GAME_HPP
