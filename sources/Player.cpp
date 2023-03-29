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
    // return (unsigned int) this->cardStack.size();
     return 1;
}

std::vector<ariel::Card> ariel::Player::getWonStack(){
    return this->wonStack;
}

unsigned int ariel::Player::getWonStackSize(){
    return this->wonStack.size();
}

void ariel::Player::setCardStack(std::vector<ariel::Card> newCardStack){
    // this->cardStack = newCardStack;
    std::cout << "call from Player::setCardStack";
}

std::vector<ariel::Card> ariel::Player::getCardStack(){
    // return this->cardStack;
    return std::vector<ariel::Card>();
}

unsigned int ariel::Player::cardesTaken(){
    // return this->nbrTotalCardsWon;
    return 1;
}

//show the back card from the cardStack
ariel::Card ariel::Player::pickCard(){
    // return this->cardStack.back();
    return ariel::Card(ariel::Card::ACE, ariel::Card::HEART);
}

void ariel::Player::addToWonStack(std::vector<ariel::Card> newcards){
    // this->wonStack.insert(
    //         this->wonStack.end(),
    //         newcards.begin(),
    //         newcards.end()
    //     );
    std::cout << "call from Player::addToWonStack" << std::endl;
}

void ariel::Player::EmptyWonStack(){
    // this->wonStack.clear();
    std::cout << "call from Player::EmptyWonStack" << std::endl;
}

// add card to the stack from the front
void ariel::Player::pushCard(std::vector<ariel::Card> cardsPushed){
   // this->cardStack.insert(
   //          this->cardStack.end(),
   //          cardsPushed.begin(),
   //          cardsPushed.end()
   //      ); 

    std::cout << "call from Player::pushCard" << std::endl;
}

ariel::Card ariel::Player::putCard(Card card){
    // ariel::Card playedCard = this->cardStack.back();
    // this->cardStack.pop_back();
    // return playedCard;
    return ariel::Card(ariel::Card::ACE, ariel::Card::HEART);
}


//Ressource:
//https://stackoverflow.com/questions/810839/throwing-exceptions-from-constructors






