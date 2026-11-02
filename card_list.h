// card_list.h
// Author: Logan Resendez
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iostream>

class CardBST
{
  struct Node;
  public:
    class Iterator
    {
        friend class CardBST;
      public:
        Iterator(Node* n = nullptr, const CardBST* t = nullptr) : curr(n), tree(t) {}

        const Card& operator*() const;
        const Card* operator->() const;

        Iterator& operator++();
        Iterator& operator--();

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {return lhs.curr == rhs.curr;}
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {return lhs.curr != rhs.curr;}

      private:
        Node* curr;
        const CardBST* tree;
    };

    CardBST();
    ~CardBST();

    CardBST(const CardBST&) = delete;
    CardBST& operator=(const CardBST&) = delete;

    bool insert(const Card& c);
    bool remove(const Card& c);
    bool contains(const Card& c) const;
    void printInOrder(std::ostream& os = std::cout) const;

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
    friend class Iterator;
    
  private:
    struct Node
    {
        Card card;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c, Node* p = nullptr) : card(c), left(nullptr), right(nullptr), parent(p) {}
    };

    Node* root;

    // Helper functions
    void clear(Node* n);
    Node* getMin(Node* n) const;
    Node* getMax(Node* n) const;
    Node* getSuccessor(Node* n) const;
    Node* getPredecessor(Node* n) const;
    Node* findNode(Node* n, const Card& c) const;
};

void playGame(CardBST& alice, CardBST& bob);

#endif
