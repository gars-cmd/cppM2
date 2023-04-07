#include <iostream>
#include <string>
#include "card.hpp"


ariel::Card::Card(ariel::Card::Value val, ariel::Card::Symbol sym)
    : value(val), symbol(sym)
    {}

ariel::Card::Card()
    : value(ariel::Card::JOKER) , symbol(ariel::Card::DEFAULT) 
    {}


ariel::Card::Value ariel::Card::getValue(){
        return value;
    }

ariel::Card::Symbol ariel::Card::getSymbol(){
        return symbol;
    }

std::string ariel::Card::toString(){
    std::string string = "";
        switch (this->value) {
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

            case 2:
                string+= "Two";
                break;
            case 3:
                string+= "Three";
                break;
            case 4:
                string+= "Four";
                break;
            case 5:
                string+= "Five";
                break;
            case 6:
                string+= "Six";
                break;
            case 7:
                string+= "Seven";
                break;
            case 8:
                string+= "Eight";
                break;
            case 9:
                string+= "Nine";
                break;
            case 10:
                string+= "Ten";
                break;
            default:
                break;
        }

        // std::cout << " of ";
         string+= " of ";

        switch (this->symbol) {
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
