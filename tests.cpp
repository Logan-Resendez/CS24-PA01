// tests.cpp
// Author: Logan Resendez
#include <iostream>
#include <cassert>
#include <sstream>
#include "card.h"
#include "card_list.h"

using namespace std;

// Card
void testCard()
{
    Card defCard;
    assert(defCard.getSuit() == 'c');
    assert(defCard.getValue() == "a");

    Card paramCard('h', "10");
    assert(paramCard.getSuit() == 'h');
    assert(paramCard.getValue() == "10");

    Card stringCard("h 10");
    assert(stringCard.getSuit() == 'h');
    assert(stringCard.getValue() == "10");

    Card cKing('c', "k");
    Card dAce('d', "a");
    Card s2('s', "2");
    Card h3('h', "3");

    assert(cKing < dAce);
    assert(dAce < s2);
    assert(s2 < h3);
    assert(h3 > cKing);

    Card hAce('h', "a");
    Card h2('h', "2");
    Card hKing('h', "k");

    assert(hAce < h2);
    assert(hKing > h2);
    assert(hKing == hKing);
    assert(hAce != hKing);

    ostringstream oss1, oss2;
    oss1 << Card('c', "a");
    assert(oss1.str() == "c a");

    oss2 << Card('h', "k");
    assert(oss2.str() == "h k");

    cout << "Card Class Passes Tests" << endl;
}

// BSTCard
void testBSTInsert()
{
    CardBST tree;
    assert(tree.insert(Card('c', "3")) == true);
    assert(tree.insert(Card('c', "a")) == true);
    assert(tree.insert(Card('d', "5")) == true);
    assert(tree.insert(Card('c', "3")) == false);
    assert(tree.insert(Card('c', "2")) == true);

    cout << "BSTInsert Passes Tests" << endl;
}

void testBSTContains()
{
    CardBST tree;
    assert(tree.contains(Card('c', "a")) == false);
    tree.insert(Card('d', "5"));
    tree.insert(Card('c', "2"));
    tree.insert(Card('s', "k"));

    assert(tree.contains(Card('d', "5")) == true);
    assert(tree.contains(Card('c', "2")) == true);
    assert(tree.contains(Card('s', "k")) == true);
    assert(tree.contains(Card('h', "a")) == false);

    cout << "BSTContains Passes Tests" << endl;
}

void testBSTRemove()
{
    CardBST tree;
    assert(tree.remove(Card('c', "a")) == false);

    tree.insert(Card('d', "5"));
    tree.insert(Card('c', "2"));
    tree.insert(Card('s', "8"));
    tree.insert(Card('c', "a"));
    tree.insert(Card('s', "4"));

    assert(tree.remove(Card('c', "a")) == true);
    assert(!tree.contains(Card('c', "a")));

    assert(tree.remove(Card('c', "2")) == true);
    assert(!tree.contains(Card('c', "2")));

    assert(tree.remove(Card('d', "5")) == true);
    assert(!tree.contains(Card('d', "5")));
    assert(tree.contains(Card('s', "4")));
    assert(tree.contains(Card('s', "8")));

    assert(tree.remove(Card('d', "5")) == false);

    cout << "BSTRemove Passes Tests" << endl;
}

void testPrintInOrder()
{
    CardBST tree;
    ostringstream oss1;
    tree.printInOrder(oss1);
    assert(oss1.str().empty());

    tree.insert(Card('c', "a"));
    ostringstream oss2;
    tree.printInOrder(oss2);
    assert(oss2.str() == "c a\n");

    tree.insert(Card('h', "10"));
    tree.insert(Card('d', "3"));
    ostringstream oss3;
    tree.printInOrder(oss3);
    assert(oss3.str() == "c a\nd 3\nh 10\n");

    tree.remove(Card('d', "3"));
    ostringstream oss4;
    tree.printInOrder(oss4);
    assert(oss4.str() == "c a\nh 10\n");

    tree.insert(Card('s', "5"));
    ostringstream oss5;
    tree.printInOrder(oss5);
    assert(oss5.str() == "c a\ns 5\nh 10\n");

    cout << "Print In Order Passes Tests" << endl;
}

// Iterator 
void testIterator()
{
    CardBST tree;
    assert(tree.begin() == tree.end());
    assert(tree.rbegin() == tree.rend());

    tree.insert(Card('c', "2"));
    auto it1 = tree.begin();
    assert(*it1 == Card('c', "2"));
    assert(it1->getSuit() == 'c');
    ++it1;
    assert(it1 == tree.end());

    tree.insert(Card('c', "a"));
    tree.insert(Card('d', "7"));
    tree.insert(Card('h', "k"));

    auto fIt = tree.begin();
    assert(*fIt == Card('c', "a")); ++fIt;
    assert(*fIt == Card('c', "2")); ++fIt;
    assert(*fIt == Card('d', "7")); ++fIt;
    assert(*fIt == Card('h', "k")); ++fIt;
    assert(fIt == tree.end());

    auto rIt = tree.rbegin();
    assert(*rIt == Card('h', "k")); --rIt;
    assert(*rIt == Card('d', "7")); --rIt;
    assert(*rIt == Card('c', "2")); --rIt;
    assert(*rIt == Card('c', "a")); --rIt;
    assert(rIt == tree.rend());

    auto itA = tree.begin();
    auto itB = tree.begin();
    assert(itA == itB);
    ++itA;
    assert(itA != itB);
    assert(fIt == tree.end());

    cout << "Iterator Passes Tests" << endl;
}

void testPlayGame()
{
    CardBST alice, bob;
    alice.insert(Card('c', "3"));
    alice.insert(Card('h', "10"));
    alice.insert(Card('s', "5"));

    bob.insert(Card('c', "3"));
    bob.insert(Card('h', "10"));
    bob.insert(Card('d', "2"));

    playGame(alice, bob);

    assert(!alice.contains(Card('c', "3")));
    assert(!bob.contains(Card('c', "3")));
    assert(!alice.contains(Card('h', "10")));
    assert(!bob.contains(Card('h', "10")));

    playGame(alice, bob);

    assert(alice.contains(Card('s', "5")));
    assert(bob.contains(Card('d', "2")));

    alice.remove(Card('s', "5"));

    playGame(alice, bob);

    assert(bob.contains(Card('d', "2")));

    cout << "Play Game Passes Tests" << endl;
}

int main()
{
    testCard();
    testBSTInsert();
    testBSTContains();
    testPrintInOrder();
    testIterator();
    testPlayGame();
    return 0;
}