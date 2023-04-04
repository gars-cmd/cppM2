#include "player.hpp"
#include "card.hpp"
#include "game.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>


ariel::Game::Game(Player player1, Player player2){
    if (player1.getName() == player2.getName()) {
        throw std::invalid_argument("both player have the same name");
    }
    this->p1 = &player1;
    this->p2 = &player2;
    this->initTheWar();
}

ariel::Player ariel::Game::getPlayer1(){
    return *this->p1;
}

ariel::Player ariel::Game::getPlayer2(){
    return *this->p2;
}


// create the regular pattern from log
void ariel::Game::add_log(std::string previous_string ,Player winner, Player looser, ariel::Card p1_card, ariel::Card p2_card){
    std::string new_log = previous_string + winner.getName() + " played " + p1_card.toString() + " " + looser.getName() +  " played " + p2_card.toString() + "." + winner.getName() + " wins.";
    this->logVector.push_back(new_log);
}

/*
 * parameter: Result obtained , Card player1 card , Card player2 card , string 
 * the string is used to store the previous logs in case of teko
 * the function is called only when a winner is obtained
 * the function call the add_log fun
*/
void ariel::Game::handlerWinner(Result result, ariel::Card card_p1, ariel::Card card_p2, std::string string){
    if (result == P1_WIN) {
        this->add_log(string,  *this->p1, *this->p2, card_p1, card_p2);
    }else if (result == P2_WIN) {
        this->add_log(string,  *this->p2, *this->p1, card_p2, card_p1);
    }

}

/*
* parameter: Card Player1 card , Card player2 card
* while the result of a new draw is not a winner make a new draw and add it to the log_string
* when a winner is found we call the function handle winner
*/
void ariel::Game::handleTeko(ariel::Card card_p1, ariel::Card card_p2){
    bool teko = true;
    Card new_p1_card = card_p1;
    Card new_p2_card = card_p2;
    std::string new_log = "";
    Result winner = find_winner(new_p1_card, new_p2_card);
    while (teko) {
    new_log +=  this->p1->getName() + " played " +new_p1_card.toString() + " " + this->p2->getName() +  " played " + new_p2_card.toString() + "." + "Draw";
        new_p1_card = this->p1->putCard();
        new_p2_card = this->p2->putCard();
        winner = find_winner(new_p1_card, new_p2_card);
        if (winner != ariel::Game::DRAW) {
            teko = false;
        }
    }
    handlerWinner(winner, card_p1, card_p2, new_log);
}



void ariel::Game::playTurn(){
    // two player draw a card from the back of their deck
    Card c_p1 = this->p1->putCard();
    Card c_p2 = this->p2->putCard();

    // compare both of the card and define who win (add to the log) 
    ariel::Game::Result winner_result = this->find_winner(c_p1, c_p2);
    if (winner_result == DRAW) {
        handleTeko(c_p1, c_p2);
    }else {
        handlerWinner(winner_result, c_p1, c_p2, "");
    }
}

void ariel::Game::playAll(){
    // tant que ?(on sait pas encore les raisons d'arret d'un jeu) alors play turn
}

std::vector<std::string> ariel::Game::getLogVector(){
    return this->logVector;
}

void ariel::Game::printLog(){
    for (size_t i = 0; i < this->logVector.size(); i++) {
        std::cout << logVector[i] << '\n';
    }
}

void ariel::Game::printStats(){

    ariel::Game::printWiner();
    std::cout << this->p1->getName() << " won " << this->p1->cardesTaken() << '\n'; 
    std::cout << this->p2->getName() << " won " << this->p2->cardesTaken() << '\n'; 
    std::cout << this->p1->getName() << " have a winrate of " << ( this->getNbrTotalDraw() ) / ( this->p1->cardesTaken() ) << "%" << '\n'; 
    std::cout << this->p2->getName() << " have a winrate of " << ( this->getNbrTotalDraw() ) / ( this->p2->cardesTaken() ) << "%" << '\n'; 
}

unsigned int ariel::Game::getNbrTotalDraw(){
    return this->nbrTotalDraw;
}

void ariel::Game::printWiner(){
    std::cout <<"the winner is " << std::max(this->p1->stacksize(),this->p2->stacksize());
}

void ariel::Game::printLastTurn(){

}

void ariel::Game::shuffleStack(std::vector<ariel::Card*>& cardStack){
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(cardStack),std::end(cardStack), rng);
}

ariel::Game::Result ariel::Game::find_winner(Card p1_card, Card p2_card){
    if (p1_card.getValue() == ariel::Card::Value::ACE && p2_card.getValue() == ariel::Card::Value::TWO) {
        return P2_WIN;
    } else if (p2_card.getValue() == ariel::Card::Value::ACE && p1_card.getValue() == ariel::Card::Value::TWO) {
        return P1_WIN;
    } else if (p1_card.getValue() > p2_card.getValue()) {
        return ariel::Game::Result::P1_WIN;
    }else if (p2_card.getValue() > p1_card.getValue()) {
        return ariel::Game::Result::P2_WIN;
    }else{
        return ariel::Game::Result::DRAW;
    }
}


std::vector<ariel::Card*> ariel::Game::generateCardStack(){
    std::vector<ariel::Card*> newCardStack ;
    for (int i = ariel::Card::HEART ; i <= ariel::Card::CLUB; i++) {
       for (int j = ariel::Card::ACE ; j <= ariel::Card::KING ; j++) {
           Card* new_card = new Card(static_cast<ariel::Card::Value>(j) , static_cast<ariel::Card::Symbol>(i));
            // std::cout << "card : " << new_card.getValue() << " of " << new_card.getSymbol() <<  '\n';
           newCardStack.push_back(new_card);
       }
    }
    return newCardStack;
}

void ariel::Game::initTheWar(){

    // create the CardStack and shuffle it 
    std::vector<ariel::Card*> CardStack = this->generateCardStack();
    std::cout << "in the stackCard there is : " << CardStack.size() << '\n';
    this->shuffleStack(CardStack);

    // Divide the CardStack into two part for each one of the player 
    std::vector<ariel::Card*> v_p1  (CardStack.begin(), CardStack.begin()  + CardStack.size()/2 );
    std::vector<ariel::Card*> v_p2  (CardStack.begin() + CardStack.size()/2 , CardStack.end() );
  
    // give both of the part to each player
    this->p1->setCardStack(v_p1);
    std::cout << "p1 have " << this->p1->getCardStack().size() << '\n';
    this->p2->setCardStack(v_p2);
    std::cout << "p2 have " << this->p2->getCardStack().size() << '\n';
}



// Ressource : 
// https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
// https://stackoverflow.com/questions/25248370/creating-a-vector-of-custom-type-objects
// https://www.tutorialkart.com/cpp/cpp-split-vector-into-two-halves/ 

