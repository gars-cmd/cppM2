#include <iostream>
#include "card.hpp"

ariel::Card::Card(Value val,Symbol sym){
        this->value = val;
        this->symbol = sym;
    }

ariel::Card::Card(){
    this->value = ariel::Card::Value::JOKER;
    this->symbol = ariel::Card::Symbol::DEFAULT;
}



ariel::Card::Value ariel::Card::getValue(){
        return value;
    }

ariel::Card::Symbol ariel::Card::getSymbol(){
        return symbol;
    }

    void ariel::Card::printCard(){
        switch (value) {
            case ACE:
                std::cout << "Ace";
                break;

            case JACK:
                std::cout << "Jack";
                break;

            case QUEEN:
                std::cout << "Queen";
                break;

            case KING:
                std::cout << "King";
                break;

            case JOKER:
                break;

            default:
                std::cout << static_cast<int>(value);
                break;
        }

        std::cout << " of ";

        switch (symbol) {
            case HEART:
                std::cout << "Heart";
                break;

            case DIAMOND:
                std::cout << "Diamond";
                break;

            case CLUB:
                std::cout << "Club";
                break;

            case SPADE:
                std::cout << "Spade";
                break;

            case DEFAULT:
                break;
        }
    }

// int main (int argc, char *argv[])
// {
//     ariel::Card ace(ariel::Card::ACE, ariel::Card::HEART); 
//     ace.printCard();
//     return 0;
// }
