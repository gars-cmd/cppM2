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

// regular constructor
ariel::Game::Game(Player& player1, Player& player2) {
    this->p1 = &player1;
    this->p2 = &player2;
    this->initTheWar();
}

ariel::Game::~Game(){
}

// copy constructor
ariel::Game::Game(const Game& other) {
    this->p1 = new Player(*other.p1);
    this->p2 = new Player(*other.p2);
    this->logVector = other.logVector;
}

//copy assignement operator
ariel::Game& ariel::Game::operator=(const Game& other)
{
    if (this != &other) {
        delete this->p1;
        delete this->p2;
        this->p1 = nullptr;
        this->p2 = nullptr;

        this->p1 = other.p1;
        this->p2 = other.p2;
    }
    return *this;
}

//move constructor
ariel::Game::Game(ariel::Game&& other) noexcept{
    p1 = other.p1;
    p2 = other.p2;
    other.p1 = nullptr;
    other.p2 = nullptr;
    logVector = std::move(other.logVector);
    cardStack = std::move(other.cardStack);
    nbrTotalTurn = other.nbrTotalTurn;
    nbrTotalDraw = other.nbrTotalDraw;
}

//move assignement operator
ariel::Game& ariel::Game::operator=(ariel::Game&& other) noexcept{
    if (this != &other) {
        delete p1;
        delete p2;

        p1 = other.p1;
        p2 = other.p2;
        other.p1 = nullptr;
        other.p2 = nullptr;
        logVector = std::move(other.logVector);
        cardStack = std::move(other.cardStack);
        nbrTotalTurn = other.nbrTotalTurn;
        nbrTotalDraw = other.nbrTotalDraw;
        other.nbrTotalTurn = 0;
        other.nbrTotalDraw = 0;
    }
    return *this;
}


ariel::Player& ariel::Game::getPlayer1(){
    return *this->p1;
}

ariel::Player& ariel::Game::getPlayer2(){
    return *this->p2;
}


// create the regular pattern from log
void ariel::Game::add_log(std::string previous_string ,Player winner, Player looser, ariel::Card p1_card, ariel::Card p2_card){
    std::string turnNbr = " ." + std::to_string(this->getNbrTotalTurn()+1) + " ";
    std::string new_log = turnNbr + previous_string  + winner.getName() + " played " + p1_card.toString() + " " + looser.getName() +  " played " + p2_card.toString() + ". " + winner.getName() + " wins." + '\n';
    this->logVector.push_back(new_log);
}

/*
 * the string is used to store the previous logs in case of teko
 * the function is called only when a winner is obtained
 * in special case when the last turn there is a teko the result var is Draw
 * in this last case the card are divided between the palyer 
 * the function call the add_log fun
*/
void ariel::Game::handlerWinner(Result result, ariel::Card card_p1, ariel::Card card_p2, std::string string){

    if (result == P1_WIN) {
        this->add_log(string,  *this->p1, *this->p2, card_p1, card_p2);
        this->p1->incNbrTurnWon();
        this->p1->incNbrCardsWonBy(2);
        this->p1->addToWonStack({card_p1,card_p2});
    }else if (result == P2_WIN){
        this->add_log(string,  *this->p2, *this->p1, card_p2, card_p1);
        this->p2->incNbrTurnWon();
        this->p2->incNbrCardsWonBy(2);
        this->p2->addToWonStack({card_p1,card_p2});
    }else {
        std::cout << "critical teko , the cards are divided between " << this->p1->getName() << " and " << this->p2->getName() << '\n';
        this->p1->addToWonStack({card_p1});
        this->p2->addToWonStack({card_p2});
    }

}


/*
 * this function is used to realized the put of the two hidden cards on teko
 * in the function each one of the player use the putCard function to drop them
 */
std::vector<ariel::Card> ariel::Game::putHiddenCards(){
    return {this->p1->putCard(), this->p2->putCard()};
}


/*
* while the result of a new draw is not a winner make a new draw and add it to the log_string
* when a winner is found we call the function handle winner
* we sum all the cards win by the winner (except for the last turn) and increment the won cards he have.
* in special case when a teko cannot be done completely we send the cards accumulated to the handleInvalidTeko func
*/
void ariel::Game::handleTeko(ariel::Card card_p1, ariel::Card card_p2){
    //init all the value needed
    bool teko = true;
    int cardAccumulated = 2; 
    Card new_p1_card = card_p1; Card new_p2_card = card_p2;
    std::string new_log = "";
    Result winner = find_winner(new_p1_card, new_p2_card);
    std::vector<Card>tekoStack;

    //while the draw do not end with a winner
    while (teko) {
        incNbrDraw();
        new_log +=  this->p1->getName() + " played " +new_p1_card.toString() + " " + this->p2->getName() +  " played " + new_p2_card.toString() + "." + " Draw. ";
        if (!checkValidityOfTeko()) {
            this->handleInvalidTeko(cardAccumulated);
            break;
        }
        std::vector<Card> tmp_teko = this->putHiddenCards();
        tekoStack.insert(tekoStack.end(),tmp_teko.begin(),tmp_teko.end());
        cardAccumulated+=2;
        new_p1_card = this->p1->putCard(); new_p2_card = this->p2->putCard();
        winner = find_winner(new_p1_card, new_p2_card);

        //exit condition (a winner was found)
        if (winner != ariel::Game::DRAW) {
            teko = false;
            if (winner == P1_WIN) {
                this->p1->incNbrCardsWonBy(cardAccumulated);
                this->p1->addToWonStack(tekoStack);
            }else {
                this->p2->incNbrCardsWonBy(cardAccumulated);
                this->p2->addToWonStack(tekoStack);
            }
         }
        else {
            cardAccumulated+=2;
        }
    }
    handlerWinner(winner, new_p1_card, new_p2_card, new_log);
}


void ariel::Game::playTurn(){
        if (this->p1->getName() == this->p2->getName()) {
        throw std::invalid_argument("both player have the same name");
    }

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
    this->nbrTotalTurn += 1; //increment the counter of turn in the game
    }
}

void ariel::Game::playAll(){
    while (this->p1->getCardStack().size() > 0) {
        this->playTurn();
    }
}

bool ariel::Game::checkValidityOfTeko(){
    bool validity = true;
    if (this->p1->stacksize() < 2) {
        validity = false;
    }
    return validity;
}

/*
 * The function check if there is an even number of cards accumulated (normal case),
 * if there is not throw an error else divide the cards by two and give them to the players
 */
void ariel::Game::handleInvalidTeko(int cardAccumulatedUntil){
    if (cardAccumulatedUntil % 2 != 0) { 
        throw std::invalid_argument("the number of card card accumulated need to be even "); 
    }
    else {
        this->p1->incNbrCardsWonBy(cardAccumulatedUntil / 2);
        this->p2->incNbrCardsWonBy(cardAccumulatedUntil / 2);
    }
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

    std::cout << "the winner of the game is : ";ariel::Game::printWiner();
    std::cout << '\t' << this->p1->getName() << " won " << this->p1->cardesTaken() << " cards." << '\n'; 
    std::cout << '\t' << this->p2->getName() << " won " << this->p2->cardesTaken() << " cards." << '\n'; 
    std::cout << '\t' << this->p1->getName() << " won " << this->p1->nbrOfTurnWon() << " turns , over " << this->nbrTotalTurn << " turns " << '\n'; 
    std::cout << '\t' <<"In the game there were " << this->getNbrTotalDraw() << " Draw." << '\n';
    std::cout << '\t' <<"The drawrate of the game is " << (static_cast<double>(this->getNbrTotalDraw()) / this->getNbrTotalTurn() *100) << "%."<< '\n';
    std::cout << '\t' << this->p1->getName() << " have a winrate of " << (static_cast<double>(this->p1->nbrOfTurnWon()) / this->nbrTotalTurn )*100 << "%." << '\n'; 
    std::cout << '\t' << this->p2->getName() << " won " << this->p2->nbrOfTurnWon() << " turns , over " << this->nbrTotalTurn << " turns." << '\n'; 
    std::cout << '\t' << this->p2->getName() << " have a winrate of " << (static_cast<double>(this->p2->nbrOfTurnWon()) / this->nbrTotalTurn )*100 << "%." << '\n'; 
}

// return the number of turn during the game
int ariel::Game::getNbrTotalTurn(){
    return this->nbrTotalTurn;
}

//return the number of Draw during the game
int ariel::Game::getNbrTotalDraw(){
    return this->nbrTotalDraw;
}

// Increase by one the counter of number of Draw during the game
void ariel::Game::incNbrDraw(){
    this->nbrTotalDraw += 1;
}

/*
* show the name of the winner according to number of cards in wonstack
* In case of teko -> print a message
*/
void ariel::Game::printWiner(){
    if (this->p1->cardesTaken() > this->p2->cardesTaken()) {
        std::cout << this->p1->getName() << '\n';
    }else if (this->p2->cardesTaken() > this->p1->cardesTaken() ) {
        std::cout << this->p2->getName() << '\n';
    }else {
        std::cout << "there is no winner , there is an equality" << '\n';
    }
}

// print the last log register in the log vector 
void ariel::Game::printLastTurn() const{
    if (!this->logVector.empty()) {
        std::cout << logVector.back() << '\n';
    }
}

// shuffle the card stack before sharing the cards between the player
void ariel::Game::shuffleStack(){
    std::random_device rd;
    auto rng = std::default_random_engine {rd()};
    std::shuffle(this->cardStack.begin(),this->cardStack.end(), rng);
}

/*
* given two cards (from player1 and player2 ) 
* return which cards win the turn , in case of Draw , return Draw 
* the return value is an enum of type Result
*/
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


// create a cardStack of 52 cards
void ariel::Game::generateCardStack(){
    for (int i = ariel::Card::HEART ; i <= ariel::Card::CLUB; i++) {
        for (int j = ariel::Card::TWO ; j <= ariel::Card::ACE ; j++) {
            Card new_card = Card(static_cast<ariel::Card::Value>(j) , static_cast<ariel::Card::Symbol>(i));
            this->cardStack.push_back(new_card);
        }
    }
}

/*
* Create a card stack 
* shuffle it 
* give the first part to player1 , the second to player2
*/
void ariel::Game::initTheWar(){

    this->generateCardStack();
    this->shuffleStack();

    // Divide the CardStack into two part for each one of the player
    vector<ariel::Card> v_p1 (this->cardStack.begin(), this->cardStack.begin() + this->cardStack.size() / 2);
    vector<ariel::Card> v_p2 (this->cardStack.begin() + this->cardStack.size() / 2, this->cardStack.end());

    // give both of the part to each player
    this->p1->setCardStack(v_p1);
    this->p2->setCardStack(v_p2);
}



// Ressource : 
// https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
// https://stackoverflow.com/questions/25248370/creating-a-vector-of-custom-type-objects
// https://www.tutorialkart.com/cpp/cpp-split-vector-into-two-halves/ 
// https://www.geeksforgeeks.org/passing-vector-constructor-c/
// https://www.freecodecamp.org/news/cpp-vector-how-to-initialize-a-vector-in-a-constructor/
// https://stackoverflow.com/questions/2551775/appending-a-vector-to-a-vector
// https://www.geeksforgeeks.org/ways-copy-vector-c/
