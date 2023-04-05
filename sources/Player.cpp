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
    this->cardStack = new std::vector<ariel::Card>;
    this->wonStack = new std::vector<ariel::Card>;

}

std::string ariel::Player::getName(){
    return  this->name;
}

void ariel::Player::setNbrCardsWon(unsigned int nbrOfWonCards){
    this->nbrTotalCardsWon+=nbrOfWonCards;
}


unsigned int ariel::Player::nbrOfTurnWon(){
    return this->nbrDrawWon;
}

void ariel::Player::incrementNbrTurnWon(){
    this->nbrDrawWon+=1;
}

unsigned int ariel::Player::stacksize(){
    return (unsigned int) this->cardStack->size();
}

std::vector<ariel::Card>* ariel::Player::getWonStack(){
    return this->wonStack;
}

void ariel::Player::setCardStack(std::vector<ariel::Card>* newCardStack){
    //make sure that the data is cleared
    this->cardStack->clear();
    for (const ariel::Card& card : *newCardStack) {
        this->cardStack->push_back(card);
    
    }
}

std::vector<ariel::Card>* ariel::Player::getCardStack(){
    return this->cardStack;
}

unsigned int ariel::Player::cardesTaken(){
    return this->wonStack->size();
}

//show the back card from the cardStack
ariel::Card ariel::Player::pickCard(){
    return this->cardStack->back();
}

void ariel::Player::addToWonStack(std::vector<ariel::Card> newcards){
    this->wonStack->insert(
            this->wonStack->end(),
            newcards.begin(),
            newcards.end()
        );
}

void ariel::Player::EmptyWonStack(){
    this->wonStack->clear();
}

void ariel::Player::printAllCards(){
    std::cout << "Card of : " << this->getName() << '\n';
    for ( ariel::Card card : *this->cardStack) {
        std::cout << card.toString() << '\n'; 
    }

}

// add card to the stack from the front
void ariel::Player::pushCard(std::vector<ariel::Card>* cardsPushed){
   this->cardStack->insert(
            this->cardStack->end(),
            cardsPushed->begin(),
            cardsPushed->end()
        ); 
}

ariel::Card ariel::Player::putCard(){
    ariel::Card playedCard = this->cardStack->back();
    this->cardStack->pop_back();
    return playedCard;
}


//Ressource:
//https://stackoverflow.com/questions/810839/throwing-exceptions-from-constructors






