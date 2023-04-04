#ifndef CARD_HPP
#define CARD_HPP

#include <string>
namespace ariel {

class Card {
public:
    enum Value {
        TWO = 2,
        THREE,
        FOUR,
        FIVE,
        SIX,
        SEVEN,
        EIGHT,
        NINE,
        TEN,
        JACK,
        QUEEN,
        KING,
        ACE,
        JOKER
    };

    enum Symbol {
        HEART,
        DIAMOND,
        SPADE,
        CLUB,
        DEFAULT
    };

private:
    Value value;
    Symbol symbol;

public:
    Card( Value val, Symbol sym);
    Card();
    Value getValue();
    Symbol getSymbol();
    std::string toString();
};


}
#endif // CARD_HPP
