#include "player.hpp"
#include "card.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <stdexcept>

ariel::Player::Player(std::string name){
    if (name.size() < 1) {
        throw std::invalid_argument("the string is empty");
    }
    this->name = name;

}

// copy constructor
ariel::Player::Player(const Player& other) {
    this->name = other.name;
    this->cardStack = other.cardStack;
    this->nbrTotalCardsWon = other.nbrTotalCardsWon;
    this->nbrDrawWon = other.nbrDrawWon;
}

// destructor
ariel::Player::~Player(){
}

//copy_assignment operator
ariel::Player& ariel::Player::operator=(const ariel::Player& other){
    if (this != &other) {
        this->name = other.name;
        this->cardStack = other.cardStack;
        this->nbrDrawWon = other.nbrDrawWon;
        this->nbrTotalCardsWon = other.nbrTotalCardsWon;
    }
    return *this;
} 

//move constructor
ariel::Player::Player(Player&& other) noexcept{
        this->name = std::move( other.name );
        this->cardStack = std::move( other.cardStack );
        this->nbrDrawWon = other.nbrDrawWon;
        this->nbrTotalCardsWon = other.nbrTotalCardsWon;
}

//move  assignment operator
ariel::Player& ariel::Player::operator=(ariel::Player&& other) noexcept{
    if (this == &other) {
        return *this;
    }
    this->cardStack.clear();
    this->name = std::move(other.name);
    this->cardStack = std::move(other.cardStack);
    this->nbrTotalCardsWon = other.nbrTotalCardsWon;
    this->nbrDrawWon = other.nbrDrawWon;

    other.name.clear();
    other.nbrDrawWon = 0;
    other.nbrTotalCardsWon = 0;
    other.cardStack.clear();
    return *this;
}


std::string ariel::Player::getName(){
    return  this->name;
}

void ariel::Player::incNbrCardsWonBy(int nbrOfWonCards){
    this->nbrTotalCardsWon+=nbrOfWonCards;
}


int ariel::Player::nbrOfTurnWon(){
    return this->nbrDrawWon;
}

void ariel::Player::incNbrTurnWon(){
    this->nbrDrawWon+=1;
}

int ariel::Player::stacksize(){
    return  this->cardStack.size();
}

std::vector<ariel::Card> ariel::Player::getWonStack(){
    return this->wonStack;
}


void ariel::Player::setCardStack(std::vector<ariel::Card>& newCardStack){
    //make sure that the data is cleared
    this->cardStack.clear();
    for (ariel::Card& card : newCardStack) {
        this->cardStack.push_back(card);
    }
}

std::vector<ariel::Card> ariel::Player::getCardStack(){
    return this->cardStack;
}

int ariel::Player::cardesTaken(){
    return this->nbrTotalCardsWon;
}

//show the back card from the cardStack
ariel::Card ariel::Player::pickCard(){
    return this->cardStack.back();
}

void ariel::Player::addToWonStack(std::vector<ariel::Card> newcards){
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
    for ( ariel::Card card : this->cardStack) {
        std::cout << card.toString() << '\n'; 
    }

}

// add card to the stack from the front
void ariel::Player::pushCard(std::vector<ariel::Card> cardsPushed){
   this->cardStack.insert(
            this->cardStack.end(),
            cardsPushed.begin(),
            cardsPushed.end()
        ); 
}

ariel::Card ariel::Player::putCard(){
    ariel::Card playedCard = this->cardStack.back();
    this->cardStack.pop_back();
    return playedCard;
}

// void ariel::Player::endOfGame(){
//     this->cardStack = this->wonStack;
// }


//Ressource:
// https://stackoverflow.com/questions/810839/throwing-exceptions-from-constructors
// https://en.cppreference.com/w/cpp/language/copy_assignment
// https://www.geeksforgeeks.org/move-constructors-in-c-with-examples/
// https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/language/move_operator.html



