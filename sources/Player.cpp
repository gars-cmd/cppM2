#include "player.hpp"
#include "card.hpp"
#include <vector>

Player::Player(std::string name){
    this->name = name;
}

std::string Player::getName(){
    return  this->name;
}

unsigned int Player::stacksize(){
    return (unsigned int) this->cardStack.size();
}

void Player::setCardStack(std::vector<Card> newCardStack){
    this->cardStack = newCardStack;
}

std::vector<Card> Player::getCardStack(){
    return this->cardStack;
}

unsigned int Player::cardesTaken(){
    return this->nbrTotalCardsWon;
}

//show the back card from the cardStack
Card Player::pickCard(){
    return this->cardStack.back();
}

void Player::addToWonStack(std::vector<Card> newcards){
    this->wonStack.insert(
            this->wonStack.end(),
            newcards.begin(),
            newcards.end()
        );
}

void Player::EmptyWonStack(){
    this->wonStack.clear();
}

// add card to the stack from the front
void Player::pushCard(std::vector<Card> cardsPushed){
   this->cardStack.insert(
            this->cardStack.end(),
            cardsPushed.begin(),
            cardsPushed.end()
        ); 
}

Card Player::putCard(Card card){
    Card playedCard = this->cardStack.back();
    this->cardStack.pop_back();
    return playedCard;
}


    





