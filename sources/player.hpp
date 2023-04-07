#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "card.hpp"
#include <string>
#include <vector>
namespace ariel {



class Player {
private:
    std::string name;
    std::vector<ariel::Card>* cardStack;
    std::vector<ariel::Card>* wonStack;
    unsigned int nbrTotalCardsWon = 0;
    unsigned int nbrDrawWon = 0;

public:
    Player(std::string name);
    ~Player();
    std::string getName();
    std::vector<ariel::Card>* getCardStack();
    void setCardStack(std::vector<ariel::Card>* newCardStack);
    unsigned int stacksize();
    unsigned int nbrOfTurnWon();
    void incNbrTurnWon();
    unsigned int cardesTaken();
    std::vector<Card>* getWonStack();
    void incNbrCardsWonBy(unsigned int nbrOfWonCards);
    void addToWonStack(std::vector<ariel::Card> newcards); 
    void EmptyWonStack();
    ariel::Card pickCard();
    void pushCard(std::vector<ariel::Card>* cardsPushed);
    ariel::Card  putCard();
    void printAllCards();
};


}

#endif
//Ressources 
//https://www.geeksforgeeks.org/stack-in-cpp-stl/rg/stack-in-cpp-stl/
