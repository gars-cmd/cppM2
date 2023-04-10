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
        std::vector<Card> cardStack; // the cardStack
        int nbrTotalTurn = 0;
        int nbrTotalDraw = 0;

    public:
    enum Result {
        P1_WIN,
        P2_WIN,
        DRAW
    };
        Game(Player& player1, Player& player2);
        ~Game();
        Game(const Game& other) ;
        Game& operator=(const Game& other);
        Game(ariel::Game&& other)noexcept;
        Game& operator=(Game&& other)noexcept;
        void playTurn();
        Player& getPlayer1();
        Player& getPlayer2();
        void playAll();
        void printLastTurn()const;
        std::vector<std::string> getLogVector();
        int getNbrTotalTurn();
        int getNbrTotalDraw();
        void incNbrDraw();
        Result find_winner(Card p1_card, Card p2_card);
        void add_log( std::string previous_string, Player winner, Player looser , ariel::Card p1_card, ariel::Card p2_card);
        void handleTeko(ariel::Card card_p1, ariel::Card card_p2);
        void handlerWinner(Result result, ariel::Card card_p1, ariel::Card card_p2, std::string string);
        void printLog();
        void printWiner();
        bool checkValidityOfTeko();
        void handleInvalidTeko(int cardAccumulatedUntil);
        void printStats();
        void generateCardStack(); //create a new card stack of 52 cards
        std::vector<Card> putHiddenCards();
        void shuffleStack(); //function that shuffle the cardStack
        void initTheWar();

};

}
#endif // GAME_HPP GAME_HPP
