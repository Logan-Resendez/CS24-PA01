// card.h
// Author: Logan Resendez
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

using namespace std;

class Card
{
  public:
    // Constructors
    Card();
    Card(char s, const string& v);
    explicit Card(const string& rawLine);

    // Accessors
    char getSuit() const;
    string getValue() const;

    // Operators
    friend bool operator==(const Card& lhs, const Card& rhs);
    friend bool operator!=(const Card& lhs, const Card& rhs);
    friend bool operator<(const Card& lhs, const Card& rhs);
    friend bool operator>(const Card& lhs, const Card& rhs);
    friend ostream& operator<<(ostream& os, const Card& c);

  private:
    // Member Variables
    char suit;
    string value;

    // Private Accessors
    int getSuitRank() const;
    int getValueRank() const;
};

#endif
