#include <iostream>
#include "card.hpp"

Card::Card(Value val, Symbol sym){
        value = val;
        symbol = sym;
    }

Card::Value Card::getValue(){
        return value;
    }

Card::Symbol Card::getSymbol(){
        return symbol;
    }

    void Card::printCard(){
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

            default:
                std::cout << static_cast<int>(value);
                break;
        }

        std::cout << "of";

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
        }
    }
