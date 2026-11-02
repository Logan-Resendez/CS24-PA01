// card_list.cpp
// Author: Logan Resendez
// Implementation of the classes defined in card_list.h

#include "card_list.h"

using namespace std;

CardBST::CardBST() : root(nullptr) {}

CardBST::~CardBST() {clear(root);}

// Private Helper Functions
void CardBST::clear(Node* n)
{
    if(!n) {return;}
    clear(n->left);
    clear(n->right);
    delete n;
}

CardBST::Node* CardBST::getMin(Node* n) const
{
    if(!n) {return nullptr;}
    while(n->left)
    {
        n = n->left;
    }
    return n;
}

CardBST::Node* CardBST::getMax(Node* n) const
{
    if(!n) {return nullptr;}
    while(n->right)
    {
        n = n->right;
    }
    return n;
}

CardBST::Node* CardBST::getSuccessor(Node* n) const
{
    if(!n) {return nullptr;}

    if(n->right)
    {
        return getMin(n->right);
    }

    Node* curr = n;
    Node* p = curr->parent;
    while(p && curr == p->right)
    {
        curr = p;
        p = p->parent;
    }
    return p;
}

CardBST::Node* CardBST::getPredecessor(Node* n) const
{
    if(!n) {return nullptr;}

    if(n->left)
    {
        return getMax(n->left);
    }

    Node* curr = n;
    Node* p = curr->parent;
    while(p && curr == p->left)
    {
        curr = p;
        p = p->parent;
    }
    return p;
}
CardBST::Node* CardBST::findNode(Node* n, const Card& c) const
{
    if(!n) {return nullptr;}
    if(c < n->card) return findNode(n->left, c);
    if(c > n->card) return findNode(n->right, c);
    return n;
}

// 
bool CardBST::insert(const Card& c)
{
    if(!root)
    {
        root = new Node(c, nullptr);
        return true;
    }

    Node* curr = root;
    Node* p = nullptr;
    while(curr)
    {
        p = curr;
        if(c < curr->card)
        {
            curr = curr->left;
        } else if(c > curr->card)
        {
            curr = curr->right;
        } else
        {
            return false;
        }
    }

    Node* newNode = new Node(c, p);
    if(newNode->card < p->card) {p->left = newNode;}
    else {p->right = newNode;}
    return true;
}

bool CardBST::remove(const Card& c)
{
    Node* target = findNode(root, c);
    if(!target) {return false;}

    if(target->left && target->right)
    {
        Node* succ = getSuccessor(target);
        target->card = succ->card;
        target = succ;
    }

    Node* child = target->left ? target->left : target->right;
    if(child)
    {
        child->parent = target->parent;
    }
    if(!target->parent)
    {
        root = child;
    } else if(target == target->parent->left)
    {
        target->parent->left = child;
    } else
    {
        target->parent->right = child;
    }

    delete target;
    return true;
}

bool CardBST::contains(const Card& c) const {return findNode(root, c) != nullptr;}

void CardBST::printInOrder(std::ostream& os) const
{
    for(auto it = begin(); it != end(); ++it)
    {
        os << *it << "\n";
    }
}

// Iterator Functions
CardBST::Iterator CardBST::begin() const
{
    return Iterator(getMin(root), this);
}

CardBST::Iterator CardBST::end() const
{
    return Iterator(nullptr, this);
}

CardBST::Iterator CardBST::rbegin() const
{
    return Iterator(getMax(root), this);
}

CardBST::Iterator CardBST::rend() const
{
    return Iterator(nullptr, this);
}

// Operators
const Card& CardBST::Iterator::operator*() const
{
    return curr->card;
}
const Card* CardBST::Iterator::operator->() const
{
    return &(curr->card);
}

CardBST::Iterator& CardBST::Iterator::operator++()
{
    if(curr && tree)
    {
        curr = tree->getSuccessor(curr);
    }
    return *this;
}

CardBST::Iterator& CardBST::Iterator::operator--()
{
    if(curr && tree)
    {
        curr = tree->getPredecessor(curr);
    }
    return *this;
}

// Play Game Function
void playGame(CardBST& alice, CardBST& bob)
{
    while (true)
    {
        bool aliceFound = false;
        Card aliceMatch;
        for(auto it = alice.begin(); it != alice.end(); ++it)
        {
            if(bob.contains(*it))
            {
                aliceMatch = *it;
                aliceFound = true;
                break;
            }
        }

        if(!aliceFound)
        {
            break;
        }
        cout << "Alice picked matching card " << aliceMatch << endl;
        alice.remove(aliceMatch);
        bob.remove(aliceMatch);

        bool bobFound = false;
        Card bobMatch;
        for(auto it = bob.rbegin(); it != bob.rend(); --it)
        {
            if(alice.contains(*it))
            {
                bobMatch = *it;
                bobFound = true;
                break;
            }
        }

        if(!bobFound)
        {
            break;
        }
        cout << "Bob picked matching card " << bobMatch << endl;
        alice.remove(bobMatch);
        bob.remove(bobMatch);
    }

    cout << "Alice's cards:" << endl;
    for(auto it = alice.begin(); it != alice.end(); ++it)
    {
        cout << *it << endl;
    }

    cout << "Bob's cards:" << endl;
    for(auto it = bob.begin(); it != bob.end(); ++it)
    {
        cout << *it << endl;
    }
}