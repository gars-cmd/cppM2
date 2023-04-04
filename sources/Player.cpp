#include "player.hpp"
#include "card.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <vector>
#include <stdexcept>

ariel::Player::Player(std::string name){
    if (name.size() < 1) {
        throw std::invalid_argument("the string is empty");
    }
    this->name = name;
}

std::string ariel::Player::getName(){
    return  this->name;
}

unsigned int ariel::Player::stacksize(){
    return (unsigned int) this->cardStack.size();
}

std::vector<ariel::Card*> ariel::Player::getWonStack(){
    return this->wonStack;
}

unsigned int ariel::Player::getWonStackSize(){
    return this->wonStack.size();
}

void ariel::Player::setCardStack(std::vector<ariel::Card*> newCardStack){
    this->cardStack = newCardStack;
}

std::vector<ariel::Card*> ariel::Player::getCardStack(){
    return this->cardStack;
}

unsigned int ariel::Player::cardesTaken(){
    return this->nbrTotalCardsWon;
}

//show the back card from the cardStack
ariel::Card ariel::Player::pickCard(){
    return *this->cardStack.back();
}

void ariel::Player::addToWonStack(std::vector<ariel::Card*> newcards){
    this->wonStack.insert(
            this->wonStack.end(),
            newcards.begin(),
            newcards.end()
        );
}

void ariel::Player::EmptyWonStack(){
    this->wonStack.clear();
}

void ariel::Player::printAllCards(){
    std::cout << "Card of : " << this->getName() << '\n';
    for (size_t i = 0; i < this->stacksize(); i++) {
        std::cout << "\t" << this->cardStack[i]->toString() << '\n';
    }
}

// add card to the stack from the front
void ariel::Player::pushCard(std::vector<ariel::Card*> cardsPushed){
   this->cardStack.insert(
            this->cardStack.end(),
            cardsPushed.begin(),
            cardsPushed.end()
        ); 
}

ariel::Card ariel::Player::putCard(){
    ariel::Card playedCard = *this->cardStack.back();
    this->cardStack.pop_back();
    return playedCard;
}


//Ressource:
//https://stackoverflow.com/questions/810839/throwing-exceptions-from-constructors






