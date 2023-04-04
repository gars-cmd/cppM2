#include <algorithm>
#include <cstddef>
#include <vector>
#include "doctest.h"
#include "sources/player.hpp"
#include "sources/game.hpp"
#include "sources/card.hpp"
#include <iostream>


#ifndef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

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
    CHECK_THROWS(Game(p1,p2));
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
    CHECK_THROWS(Game(p1,p1));
}


// 4.
TEST_CASE("test that at the begining of the game both of the player have 0 cards"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    bool p1_res = p1.stacksize() == 0 ;
    bool p2_res = p2.stacksize() == 0 ;
    CHECK(  ((p1_res)  &&  (p2_res))  );
}


// 5.
TEST_CASE("test that at the begining the cardStack is shuffled"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    std::vector<Card> v1;
    for (int i = ariel::Card::HEART ; i <= ariel::Card::CLUB; i++) {
       for (int j = ariel::Card::ACE ; j <= ariel::Card::KING ; j++) {
           Card new_card(static_cast<ariel::Card::Value>(j) , static_cast<ariel::Card::Symbol>(i));
           v1.push_back(new_card);
       }
    }
    std::cout << v1.size() << '\n';
    std::vector<Card*> v2 = g1.generateCardStack();
    std::cout << v2.size() << '\n';
    
    bool cond = true;
    for (size_t i = 0; i < v1.size() ; i++) {
        if (v1[i].getValue() != v2[i]->getValue()) {
            cond = false;
        }
    }
    CHECK(cond);
}


// 6.
TEST_CASE("test that both of the player have 26 cards"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    g1.initTheWar();
    g1.getPlayer1().printAllCards();
    g1.getPlayer2().printAllCards();
    bool s1 = p1.stacksize() == 26;
    bool s2 = p2.stacksize() == 26;
    CHECK((  s1  &&  s2 ));
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
    unsigned int initSize = p1.stacksize();
    p1.putCard();
    CHECK(p1.stacksize() == initSize - 1);
}


// 9.
TEST_CASE("test that a player play a card at a turn"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    Card compareCard = p1.putCard();
    bool c1 = compareCard.getValue() <= Card::KING;
    bool c2 = compareCard.getValue() >= Card::ACE;
    bool c3 = compareCard.getSymbol() >= Card::HEART;
    bool c4 = compareCard.getSymbol() <= Card::CLUB;
    bool c5 = c1 && c2;
    bool c6 = c3 && c4;
    CHECK((c5 && c6));
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
    bool W1 = p1.getWonStackSize() > p1Wonstack; 
    bool W2 = p2.getWonStackSize() > p2Wonstack; 

    CHECK( (W1 || W2) );
}


// 12.
TEST_CASE("test that at the begining of the game each one have the won stack empty"){
    Player p1("player1");
    Player p2("player2");
    unsigned int p1Wonstack = p1.getWonStackSize();
    unsigned int p2Wonstack = p2.getWonStackSize();
    bool bp1Wonstack = (int) p1Wonstack == 0;
    bool bp2Wonstack = (int) p2Wonstack == 0;

    CHECK( ( bp1Wonstack  &&  bp2Wonstack ) ) ;
}


// 13.
TEST_CASE("test that there is same number of log that number of turn"){

    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    g1.playAll();
    CHECK(g1.getLogVector().size() == g1.getNbrTotalDraw());
}


// 14.
TEST_CASE("test the printing of the cards"){
    Card aceOfHeart(Card::ACE, Card::HEART);
    Card treeOfSpade(Card::THREE, Card::SPADE);
    CHECK(aceOfHeart.toString()=="Ace of Heart");
    CHECK(treeOfSpade.toString()=="Three of Spade");
}

// 15.
TEST_CASE("basic creation case of card"){
    Card card1(Card::Value::ACE, Card::Symbol::HEART);
    Card card2(Card::Value::FIVE, Card::Symbol::DIAMOND);
    CHECK(card1.getValue() == Card::Value::ACE);
    CHECK(card1.getSymbol() == Card::Symbol::HEART);
    CHECK(card2.getValue() == Card::Value::FIVE);
    CHECK(card2.getSymbol() == Card::Symbol::DIAMOND);
}

// 16.
TEST_CASE("test the name of the player"){
    
    Player p1("name1");
    Player p2("name2");
    CHECK(p1.getName()=="name1");
    CHECK(p2.getName()=="name2");
}

// 17.
TEST_CASE("test that the name given for the player is not empty"){
    CHECK_THROWS(Player(""));
}

// 18.
TEST_CASE("test that the winner of the round get all the cards from the win stack"){
    Player p1("player1");
    Player p2("player2");
    Game g1(p1,p2);
    g1.playTurn();
    bool cond1 = p1.stacksize() == (26 + (26 - p2.stacksize())); 
    bool cond2 = p2.stacksize() == (26 + (26 - p1.stacksize())); 
CHECK( (cond1 || cond2) );
}

//Ressource:
//https://stackoverflow.com/questions/5129498/how-to-cast-or-convert-an-unsigned-int-to-int-in-c

#endif
