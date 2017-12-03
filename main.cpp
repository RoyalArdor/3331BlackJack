#include <iostream>
#include <vector>
#include "user.h"
#include "player.h"
#include "dealer.h"
#include "card.h"
#include <string>
#define MINIMUM_BET 5
#define MAXIMUM_BET 100
using namespace std;

vector<Player*> players;
Dealer dealer;
string globalInput;
Player *playerTurn;

void PrintIntro(){
  cout << "======================"
    <<    "|Welcome to Blackjack|"
    <<    "======================" << endl;
}
vector<Player*> SetPlayers(vector<Player*>& _p){
  int _numOfPlayers;
  cout << "How many players? (1-5)\n";
  cin >> _numOfPlayers;

  while(_numOfPlayers <1 || _numOfPlayers >5){
    cout << "Please enter a number from 1 to 5.\n";
    cin >> _numOfPlayers;
  }

  for(int i=0; i< _numOfPlayers;i++){
    cout << "creating player " << i+1 << endl;
    Player* temp = new Player(i+1);
    _p.push_back(temp);
  }
  // cout << "players set, size: " << _p.size() << endl;
  playerTurn = _p[0];
  return _p;
}

void DealInitial(Dealer &d, vector<Player*> &p){
  for(int i=0; i<2; i++){
    // cout<< "dealing card to dealer\n";
    dealer.DealFromDeck(d);
    // cout <<"size of player vector: " << p.size() << endl;
    for (int j=0; j< static_cast<int>(p.size()); j++){
      // cout<< "dealing card to player\n";
      dealer.DealFromDeck(*p.at(j));
    }
  }
  Card::FlipCard(dealer.GetCard(1));
}

void PrintTable(Dealer &d, vector<Player*> &p){
  cout << "PLAYER\t\tCARDS" << endl
    <<    "------\t\t-----"<<endl;
  cout << "Dealer: \t";
  for(int i=0; i< d.GetHand().size(); i++){
    cout << d.GetHand().at(i) << ", ";
  }
  cout << endl;

  for(int i=0; i< p.size(); i++){
    cout << "Player " << i+1 << ":\t";
    for(int j=0; j< p.at(i)->GetHand().size(); j++){
      cout << p.at(i)->GetHand().at(j) << ", ";
    }
    cout << "\tBalance: $ " << p.at(i)->GetBalance() << endl;
  }
}

void PlaceBets(Player *p, vector<Player*> &_players, string& _input){
  for(int i = 0; i< _players.size(); i++){
    cout << "Player " << p->GetID() << "'s turn\n"
      << "Place your bet ($" << MINIMUM_BET << " to $" << MAXIMUM_BET <<")"<< endl;
    cin >> _input;
    if(p->GetBalance()>=5){ //check balance

      while(stoi(_input) < 5 || stoi(_input)>100){  //ensure balance in range for bet
        cout << "type an amount from $" << MINIMUM_BET << " to $" << MAXIMUM_BET <<"."<< endl;
        cin >> _input;
      }

      p->SetAnte(stoi(_input));
      //change player turn
      if(i+1==_players.size()){
        p=_players.at(0); //last player goes back to beginning
      }
      else{
        p = _players.at(i+1);
        }
    }
    else{ 
      cout << "your balance is too low (Player " << p->GetID()<<" kicked from the game)." << endl;
      _players.erase(_players.begin()+i); //remove player if balance too low
    }
  }
}

int main(){
  PrintIntro();
  SetPlayers(players);
  PlaceBets(playerTurn, players, globalInput);
  DealInitial(dealer, players);
  PrintTable(dealer, players);
  cout << dealer.GetDeckSize()<< endl;
  system("Pause");
}