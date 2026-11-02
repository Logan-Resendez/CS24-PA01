// This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

using namespace std;

int main(int argv, char** argc){
  if(argv < 3){
    cout << "Please provide 2 file names" << endl;
    return 1;
  }
  
  ifstream cardFile1 (argc[1]);
  ifstream cardFile2 (argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail() ){
    cout << "Could not open file " << argc[2];
    return 1;
  }

  set<Card> alice;
  set<Card> bob;

  //Read each file
  while (getline (cardFile1, line) && (line.length() > 0)){
    alice.insert(Card(line));
  }
  cardFile1.close();


  while (getline (cardFile2, line) && (line.length() > 0)){
    bob.insert(Card(line));
  }
  cardFile2.close();
  
  // Game Loop
  while(true)
  {
    bool aliceFound = false;
    Card aliceMatch;
    for(auto it = alice.begin(); it != alice.end(); ++it)
    {
      if(bob.find(*it) != bob.end())
      {
        aliceMatch = *it;
        aliceFound = true;
        break;
      }
    }

    if(!aliceFound){break;}

    cout << "Alice picked matching card " << aliceMatch << endl;
    alice.erase(aliceMatch);
    bob.erase(aliceMatch);

    bool bobFound = false;
    Card bobMatch;
    for(auto it = bob.rbegin(); it != bob.rend(); ++it)
    {
      if(alice.find(*it) != alice.end())
      {
        bobMatch = *it;
        bobFound = true;
        break;
      }
    }

    if(!bobFound){break;}

    cout << "Bob picked matching card " << bobMatch << endl;
    alice.erase(bobMatch);
    bob.erase(bobMatch);
  }
  cout << endl << endl;

  // Print hands
  cout << "Alice's cards:" << endl;
  for(const auto& c : alice){cout << c << endl;}
  cout << endl;
  cout << "Bob's cards:" << endl;
  for(const auto& c : bob){cout << c << endl;}
  
  return 0;
}
