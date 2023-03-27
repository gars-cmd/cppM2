#ifndef CARD_HPP
#define CARD_HPP

namespace ariel {

class Card {
public:
    enum Value {
        ACE = 1,
        TWO,
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
        KING
    };

    enum Symbol {
        HEART,
        DIAMOND,
        SPADE,
        CLUB
    };

private:
    Value value;
    Symbol symbol;

public:
    Card(Value val, Symbol sym);
    Value getValue();
    Symbol getSymbol();
    void printCard();
};


}
#endif // CARD_HPP
