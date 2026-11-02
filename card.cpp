// card.cpp
// Author: Logan Resendez
// Implementation of the classes defined in card.h

#include "card.h"
#include <sstream>

Card::Card()
{
    suit = 'c';
    value = "a";
}

Card::Card(char s, const string& v)
{
    suit = s;
    value = v;
}

Card::Card(const string& rawLine)
{
    stringstream ss(rawLine);
    ss >> suit >> value;
}

char Card::getSuit() const {return suit;}

string Card::getValue() const {return value;}

bool operator==(const Card& lhs, const Card& rhs) {return(lhs.suit == rhs.suit && lhs.value == rhs.value);}

bool operator !=(const Card& lhs, const Card& rhs) {return !(lhs == rhs);}

bool operator<(const Card& lhs, const Card& rhs)
{
    if(lhs.getSuitRank() != rhs.getSuitRank())
    {
        return lhs.getSuitRank() < rhs.getSuitRank();
    }
    return lhs.getValueRank() < rhs.getValueRank();
}

bool operator>(const Card& lhs, const Card& rhs)
{
    if(lhs.getSuitRank() != rhs.getSuitRank())
    {
        return lhs.getSuitRank() > rhs.getSuitRank();
    }
    return lhs.getValueRank() > rhs.getValueRank();
}

ostream& operator<<(ostream& os, const Card& c) {return os << c.suit << " " << c.value;}

int Card::getSuitRank() const
{
    switch(suit)
    {
        case 'c': return 0;
        case 'd': return 1;
        case 's': return 2;
        case 'h': return 3;
        default: return -1;
    }
}

int Card::getValueRank() const
{
    if(value == "a") {return 1;}
    if(value == "j") {return 11;}
    if(value == "q") {return 12;}
    if(value == "k") {return 13;}
    return stoi(value);
}