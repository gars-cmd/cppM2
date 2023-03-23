#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <string>
#include <vector>

class Player {
private:
    std::string name;
    std::vector<Card> cardStack;
    std::vector<Card> wonStack;
    unsigned int nbrTotalCardsWon = 0;
    unsigned int nbrDrawWon = 0;

public:
    Player(std::string name);
    std::string getName();
    std::vector<Card> getCardStack();
    void setCardStack(std::vector<Card> newCardStack);
    unsigned int stacksize();
    unsigned int cardesTaken();
    void setNbrCardsWon();
    void addToWonStack(std::vector<Card> newcards); 
    void EmptyWonStack();
    Card pickCard();
    void pushCard(std::vector<Card> cardsPushed);
    Card putCard(Card card);
};

#endif

//Ressources 
//https://www.geeksforgeeks.org/stack-in-cpp-stl/
