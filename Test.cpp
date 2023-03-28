#include <algorithm>
#include <cstddef>
#include <vector>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"

using namespace ariel;
// int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }
//
// TEST_CASE("testing the factorial function") {
//     CHECK(factorial(1) == 1);
//     CHECK(factorial(2) == 2);
//     CHECK(factorial(3) == 6);
//     CHECK(factorial(10) == 3628800);
// }


// 1.
TEST_CASE("same name for both of the player in the game -> NULL") {
Player p1("name");
Player p2("name");
Game g1(p1,p2);
CHECK(g1.generateCardStack() == std::vector<Card>(0));
}

// 2.
TEST_CASE("the stackCard is less or more than 52 cards"){
    Player p1("George");
    Player p2("David");
    Game g1(p1,p2);
    CHECK ( g1.generateCardStack().size()  == 52 );
}

// 3.
TEST_CASE("test that the game can be initialized with 2 player only"){
    Player p1("player1");
    Game g1(p1,p1);
    CHECK(g1.generateCardStack().size() == 0);
}


// 4.
TEST_CASE("test that at the begining of the game both of the player have 0 cards"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    CHECK(p1.stacksize() == p2.stacksize() == 0);
}


// 5.
TEST_CASE("test that at the begining the cardStack is shuffled"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    std::vector<Card> v1(52);
    for (int i = ariel::Card::HEART ; i <= ariel::Card::CLUB; i++) {
       for (int j = ariel::Card::ACE ; j <= ariel::Card::KING ; j++) {
           Card new_card(static_cast<ariel::Card::Value>(j) , static_cast<ariel::Card::Symbol>(i));
           v1.push_back(new_card);
       }
    }
    std::vector<Card> v2 = g1.generateCardStack();
        CHECK(std::equal(v1.begin(),v1.end(),v2.begin(),v2.end()) == false);
}


// 6.
TEST_CASE("test that both of the player have 26 cards"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    CHECK(p1.stacksize() == p2.stacksize() == 26);
}


// 7.
TEST_CASE("test that both of the player have the same ammount of card after oen turn"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    g1.playTurn();
    CHECK(p1.stacksize() == p2.stacksize());
}


// 8.
TEST_CASE("test that a player play a card at a turn"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    int initSize = p1.stacksize();
    p1.putCard(p1.getCardStack()[0]);
    CHECK(p1.stacksize() == initSize - 1);
}


// 9.
TEST_CASE("test that a player play a card at a turn"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    Card compareCard = p1.putCard(p1.getCardStack()[0]);
    CHECK(compareCard.getValue() <= Card::KING &&
          compareCard.getValue() >= Card::ACE &&
          compareCard.getSymbol() >= Card::HEART &&
          compareCard.getSymbol() <= Card::CLUB);
}


// 10.
TEST_CASE("test that the big card win the weak one"){
    Card strong(Card::KING,Card::HEART);
    Card weak(Card::QUEEN,Card::CLUB);
    CHECK(strong.getValue() > weak.getValue());
}



// 11.
TEST_CASE("test that after a turn one of the player has increased his wonsatck"){
    Player p1("player1");
    Player p2("player2");
    unsigned int p1Wonstack = p1.getWonStackSize();
    unsigned int p2Wonstack = p2.getWonStackSize();
    Game g1(p1,p2);
    g1.playTurn();

    CHECK(p1.getWonStackSize() > p1Wonstack ||
          p2.getWonStackSize() > p2Wonstack);
}


// 12.
TEST_CASE("test that at the begining of the game each one have the won stack epty"){
    Player p1("player1");
    Player p2("player2");
    unsigned int p1Wonstack = p1.getWonStackSize();
    unsigned int p2Wonstack = p2.getWonStackSize();

    CHECK(p1Wonstack == p2Wonstack == 0);
}



