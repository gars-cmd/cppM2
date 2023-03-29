#include <iostream>
#include <string>
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

std::string ariel::Card::toString(){
    std::string string = "";
        switch (value) {
            case ACE:
                // std::cout << "Ace";
                string+="Ace";
                break;

            case JACK:
                // std::cout << "Jack";
                string+="Jack";
                break;

            case QUEEN:
                // std::cout << "Queen";
                string+="Queen";
                break;

            case KING:
                // std::cout << "King";
                string+="King";
                break;

            case JOKER:
                break;

            default:
                // std::cout << static_cast<int>(value);
                string+=static_cast<int>(value);
                break;
        }

        // std::cout << " of ";
         string+= " of ";

        switch (symbol) {
            case HEART:
                // std::cout << "Heart";
                string+="Heart";
                break;

            case DIAMOND:
                // std::cout << "Diamond";
                string+="Diamond";
                break;

            case CLUB:
                // std::cout << "Club";
                string+="Club";
                break;

            case SPADE:
                // std::cout << "Spade";
                string+="Spade";
                break;

            case DEFAULT:
                break;
        }
    return string;
    }

//Ressources : 
//https://www.youtube.com/watch?v=1nfuYMXjZsA&t=186s
