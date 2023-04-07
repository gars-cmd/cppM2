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

using std::vector;

ariel::Game::Game(Player player1, Player player2) {
    if (player1.getName() == player2.getName()) {
        throw std::invalid_argument("both player have the same name");
    }
    this->p1 = &player1;
    this->p2 = &player2;
    this->cardStack = new std::vector<ariel::Card>;
    this->initTheWar();
}

ariel::Game::~Game(){
    delete cardStack;
    // delete p1;
    // delete p2;
}

ariel::Player& ariel::Game::getPlayer1(){
    return *this->p1;
}

ariel::Player& ariel::Game::getPlayer2(){
    return *this->p2;
}


// create the regular pattern from log
void ariel::Game::add_log(std::string previous_string ,Player winner, Player looser, ariel::Card p1_card, ariel::Card p2_card){
    std::string new_log = previous_string  + winner.getName() + " played " + p1_card.toString() + " " + looser.getName() +  " played " + p2_card.toString() + ". " + winner.getName() + " wins." + '\n';
    this->logVector.push_back(new_log);
}

/*
 * the string is used to store the previous logs in case of teko
 * the function is called only when a winner is obtained
 * the function call the add_log fun
*/
void ariel::Game::handlerWinner(Result result, ariel::Card card_p1, ariel::Card card_p2, std::string string){
    // std::vector<Card> won_cards {card_p1,card_p2};
    if (result == P1_WIN) {
        this->add_log(string,  *this->p1, *this->p2, card_p1, card_p2);
        this->p1->incNbrTurnWon();
        // this->p1->addToWonStack(won_cards);
        this->p1->incNbrCardsWonBy(2);
    }else{
        this->add_log(string,  *this->p2, *this->p1, card_p2, card_p1);
        this->p2->incNbrTurnWon();
        // this->p2->addToWonStack(won_cards);
        this->p2->incNbrCardsWonBy(2);
    }

}


/*
 * this function is used to realized the put of the two hidden cards on teko
 * in the function each one of the player use the putCard function to drop them
 */
void ariel::Game::putHiddenCards(){
    this->p1->putCard();
    this->p2->putCard();
}


/*
* while the result of a new draw is not a winner make a new draw and add it to the log_string
* when a winner is found we call the function handle winner
* we add the won cards to the wonstack of each players
* we add the number of cards won by the winner to the number of cards won
* at each turn we add to the tekostack the new cards drawn
*/
void ariel::Game::handleTeko(ariel::Card card_p1, ariel::Card card_p2){
    //init all the value needed
    bool teko = true;
    unsigned int cardAccumulated = 2; 
    Card new_p1_card = card_p1; Card new_p2_card = card_p2;
    std::string new_log = "";
    Result winner = find_winner(new_p1_card, new_p2_card);

    //while the draw do not end with a winner
    while (teko) {
        new_log +=  this->p1->getName() + " played " +new_p1_card.toString() + " " + this->p2->getName() +  " played " + new_p2_card.toString() + "." + " Draw. ";
        bool validity = this.checkValidityOfTeko(cardAccumulated);
        this->putHiddenCards();
        cardAccumulated+=2;
        new_p1_card = this->p1->putCard(); new_p2_card = this->p2->putCard();
        winner = find_winner(new_p1_card, new_p2_card);

        //exit condition (a winner was found)
        if (winner != ariel::Game::DRAW) {
            teko = false;
            if (winner == P1_WIN) {
                this->p1->incNbrCardsWonBy(cardAccumulated);
            }else {
                this->p2->incNbrCardsWonBy(cardAccumulated);
            }
         }
        else {
            cardAccumulated+=2;
        }
    }
    handlerWinner(winner, new_p1_card, new_p2_card, new_log);
}


void ariel::Game::playTurn(){
    if (this->p1->stacksize() < 1 || this->p2->stacksize() < 1) {
        throw::std::length_error("there is no more cards to play with");
    }
    else {
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
    this->nbrTotalDraw += 1; //increment the counter of turn in the game
    }
}

void ariel::Game::playAll(){
    while (this->p1->getCardStack()->size() > 0) {
        this->playTurn();
    }
    std::cout << "end of game :" << '\n' ; 
}

bool ariel::Game::checkValidityOfTeko(){
    bool validity = true;
    if (this->p1->stacksize() < 2) {
        validity = false;
    }
    return validity;
}

void ariel::Game::handleInvalidTeko(unsigned int cardAccumulatedUntil){
    
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
    std::cout << '\t' << this->p1->getName() << " won " << this->p1->cardesTaken() << "cards" << '\n'; 
    std::cout << '\t' << this->p2->getName() << " won " << this->p2->cardesTaken() << "cards" << '\n'; 
    std::cout << '\t' << this->p1->getName() << " won " << this->p1->nbrOfTurnWon() << " turns , over " << this->nbrTotalDraw << " turns " << '\n'; 
    std::cout << '\t' << this->p1->getName() << " have a winrate of " << (static_cast<double>(this->p1->nbrOfTurnWon()) / this->nbrTotalDraw )*100 << "%" << '\n'; 
    std::cout << '\t' << this->p2->getName() << " won " << this->p2->nbrOfTurnWon() << " turns , over " << this->nbrTotalDraw << " turns " << '\n'; 
    std::cout << '\t' << this->p2->getName() << " have a winrate of " << (static_cast<double>(this->p2->nbrOfTurnWon()) / this->nbrTotalDraw )*100 << "%" << '\n'; 
}

unsigned int ariel::Game::getNbrTotalDraw(){
    return this->nbrTotalDraw;
}

/*
* show the name of the winner according to number of cards in wonstack
* In case of teko -> need to implement
* use of ternary operator.
*/
void ariel::Game::printWiner(){
    ( this->p1->cardesTaken() > this->p2->cardesTaken() )? 
        std::cout << this->p1->getName() << '\n' 
        : std::cout << this->p2->getName() << '\n';
}

void ariel::Game::printLastTurn(){
    std::cout << this->logVector.back() << '\n';
}

void ariel::Game::shuffleStack(){
    std::random_device rd;
    auto rng = std::default_random_engine {rd()};
    std::shuffle(this->cardStack->begin(),this->cardStack->end(), rng);
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


void ariel::Game::generateCardStack(){
    for (int i = ariel::Card::HEART ; i <= ariel::Card::CLUB; i++) {
        for (int j = ariel::Card::TWO ; j <= ariel::Card::ACE ; j++) {
            Card new_card = Card(static_cast<ariel::Card::Value>(j) , static_cast<ariel::Card::Symbol>(i));
            // std::cout << "card : " << new_card.getValue() << " of " << new_card.getSymbol() <<  '\n';
            this->cardStack->push_back(new_card);
        }
    }
}

void ariel::Game::initTheWar(){

    // create the CardStack and shuffle it 
    this->generateCardStack();
    // std::cout << "in the stackCard there is : " << this->cardStack->size() << '\n';
    this->shuffleStack();

    // Divide the CardStack into two part for each one of the player
    vector<ariel::Card>* v_p1 = new std::vector<ariel::Card>(this->cardStack->begin(), this->cardStack->begin() + this->cardStack->size() / 2);
    vector<ariel::Card>* v_p2 = new std::vector<ariel::Card>(this->cardStack->begin() + this->cardStack->size() / 2, this->cardStack->end());

    // give both of the part to each player
    this->p1->setCardStack(v_p1);
    // std::cout << "p1 have " << this->p1->getCardStack()->size() << '\n';
    // this->p1->printAllCards();
    this->p2->setCardStack(v_p2);
    // std::cout << "p2 have " << this->p2->getCardStack()->size() << '\n';
    // this->p2->printAllCards();
    delete v_p1;
    delete v_p2;
}



// Ressource : 
// https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
// https://stackoverflow.com/questions/25248370/creating-a-vector-of-custom-type-objects
// https://www.tutorialkart.com/cpp/cpp-split-vector-into-two-halves/ 
// https://www.geeksforgeeks.org/passing-vector-constructor-c/
// https://www.freecodecamp.org/news/cpp-vector-how-to-initialize-a-vector-in-a-constructor/

