#include "player.hpp"
#include "card.hpp"
#include "game.hpp"
#include <algorithm>
#include <iterator>
#include <random>
#include <iostream>
#include <vector>


ariel::Game::Game(Player player1, Player player2){
    this->p1 = &player1;
    this->p2 = &player2;
}


void ariel::Game::playTurn(){
   std::cout<< "test from playturn" << std::endl;
}

void ariel::Game::playAll(){
   std::cout<< "test from play all turn" << std::endl;
}

void ariel::Game::printLog(){

   std::cout<< "test from print all Log" << std::endl;
}

void ariel::Game::printStats(){

   std::cout<< "test from print stats" << std::endl;
}

void ariel::Game::printWiner(){
    // std::cout <<"the winner is " << std::max(this->p1->stacksize(),this->p2->stacksize());
    std::cout << "call from Game::printWiner" << std::endl;
}

void ariel::Game::printLastTurn(){

   std::cout<< "print from print last turn" << std::endl;
}

void ariel::Game::shuffleStack(std::vector<ariel::Card> &cardStack){
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(cardStack), std::end(cardStack), rng);
}


std::vector<ariel::Card> ariel::Game::generateCardStack(){
    // std::vector<ariel::Card> newCardStack(52) ;
    // for (int i = ariel::Card::HEART ; i <= ariel::Card::CLUB; i++) {
    //    for (int j = ariel::Card::ACE ; j <= ariel::Card::KING ; j++) {
    //        Card new_card(static_cast<ariel::Card::Value>(j) , static_cast<ariel::Card::Symbol>(i));
    //        newCardStack.push_back(new_card);
    //    }
    // }
    // return newCardStack;
    return std::vector<ariel::Card>();
}



// SOURCES : 
// https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector

