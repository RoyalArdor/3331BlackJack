#include "BlackJack.h"
#include "BlackJack.h"
#include <iostream>
#include <vector>
#include "User.h"
#include "Player.h"
#include "Dealer.h"
#include "Card.h"
#include <string>
#include <algorithm>
#define MINIMUM_BET 5
#define MAXIMUM_BET 100
#define MINIMUM_PLAYERS 1
#define MAXIMUM_PLAYERS 5
using namespace std;

void BlackJack::PrintIntro(){
  cout << " ====================\n"
    <<    "|Welcome to Blackjack|\n"
    <<    " ====================" << endl;
}

void BlackJack::SetPlayers(vector<Player*> &p, double startingBalance){
  int _numOfPlayers;
  cout << "How many players? ("<< MINIMUM_PLAYERS << "-" << MAXIMUM_PLAYERS << ")\n";
  cin >> _numOfPlayers;

  while(_numOfPlayers < MINIMUM_PLAYERS || _numOfPlayers > MAXIMUM_PLAYERS){
    cout << "Please enter a number from "<< MINIMUM_PLAYERS << " to " << MAXIMUM_PLAYERS << ".\n";
    cin >> _numOfPlayers;
  }

  for(int i=0; i< _numOfPlayers;i++){
    //cout << "creating player " << i+1 << endl;
    Player* temp = new Player(i+1, startingBalance);
    p.push_back(temp);
  }
  // cout << "players set, size: " << _p.size() << endl;
}

void BlackJack::DealInitial(Dealer &d, vector<Player*> &p){
  //cout<< "dealing two cards" << endl;
  for(int i=0; i<2; i++){
    // cout<< "dealing card to dealer\n";
    d.DealFromDeck(d);
    // cout <<"size of player vector: " << p.size() << endl;
    for (int j=0; j< static_cast<int>(p.size()); j++){
      // cout<< "dealing card to player\n";
      if(p.at(j)->GetStatus()!=Status::LOWBALANCE){
        d.DealFromDeck(*p.at(j));
      }
    }
  }
  Card::FlipCard(d.GetCard(0));
}

void BlackJack::PrintTable(Dealer &d, vector<Player*> &p){
  cout << "\nPLAYER\t\tCARDS = [POSSIBLE VALUES]" << endl
    <<    "------\t\t-------------------------"<<endl;
  cout << "Dealer: \t";
  for(int i=0; i< d.GetHand().size(); i++){
    cout << d.GetHand().at(i) << ", ";
  }
  cout << " = [";
  for(int j=0; j< Card::GetHandValues(d.GetHand()).size(); j++){
    cout << Card::GetHandValues(d.GetHand()).at(j)<< ", ";
  }
  cout << "]";
  cout << endl;

  for(int i=0; i< p.size(); i++){
    cout << "Player " << i+1 << ":\t";
    if(p.at(i)->GetStatus()!=Status::LOWBALANCE){
      for(int j=0; j< p.at(i)->GetHand().size(); j++){
        cout << p.at(i)->GetHand().at(j) << ", ";
      }
      cout << " = [";
      for(int j=0; j< Card::GetHandValues(p.at(i)->GetHand()).size(); j++){
        cout << Card::GetHandValues(p.at(i)->GetHand()).at(j)<< ", ";
      }
      cout << "]\t\t";
    }
    cout << "Balance: $ " << p.at(i)->GetBalance();
    if(p.at(i)->GetStatus()!=Status::LOWBALANCE){
      cout << "\tAnte: $ " << p.at(i)->GetAnte();
    }
    cout << "\tStatus: ";
    switch(p.at(i)->GetStatus()) {
      case Status::BUST:  
                          cout << "BUST";
                          break;
      case Status::WAITING:   
                          cout << "WAITING FOR DEALER";
                          break;
      case Status::DOUBLEDDOWN:
                          cout << "DOUBLEDDOWNED";
                          break;
      case Status::HIT:
                          cout << "HIT";
                          break;
      case Status::STAY:  
                          cout << "STAY";
                          break;
      case Status::FOLD:  
                          cout << "FOLD";
                          break;
      case Status::INITIAL: 
                          cout << "";
                          break;
      case Status::WIN: 
                          cout << "WIN";
                          break;
      case Status::LOSE: 
                          cout << "LOSE";
                          break;
      case Status::TIE: 
                          cout << "TIE";
                          break;
      case Status::LOWBALANCE: 
                          cout << "LOW BALANCE";
                          break;
      default: cout << "";
    }
    cout << endl;
  }
  cout << endl;
}

void BlackJack::PlaceBets(vector<Player*> &p){
  string _input;

  cout << "\t\tBetting Phase..."<< endl;

  for(int i = 0; i< p.size(); i++){
    if(p.at(i)->GetStatus() != Status::LOWBALANCE){
      if(p.at(i)->GetBalance() < double(MINIMUM_BET)){ //check balance
        cout << "\t\tYour balance is too low, Player " << p.at(i)->GetID() << endl;
        p.at(i)->SetStatus(Status::LOWBALANCE); //set player to low balance status if lower than minimum bet
      }
    }
    if(p.at(i)->GetStatus() != Status::LOWBALANCE){
      cout << "Player " << p.at(i)->GetID() << "'s turn\n"
        << "Place your bet ($" << MINIMUM_BET << " to $" << MAXIMUM_BET <<")"<< endl;
      cin >> _input;

      while(atof(_input.c_str()) < double(MINIMUM_BET) || atof(_input.c_str()) > double(MAXIMUM_BET) || atof(_input.c_str()) > p.at(i)->GetBalance()){  //ensure balance in range for bet
        if(atof(_input.c_str()) > p.at(i)->GetBalance() && atof(_input.c_str()) <= double(MAXIMUM_BET) ){
          cout << "type an amount from $" << MINIMUM_BET << " to $" << p.at(i)->GetBalance() <<"."<< endl;
        }
        else {
          cout << "type an amount from $" << MINIMUM_BET << " to $" << MAXIMUM_BET <<"."<< endl;
        }
        cin >> _input;
      }
      p.at(i)->AddAnte(atof(_input.c_str()));
    }
  }
}

//Check every player's hand whether they win or bust
void BlackJack::CheckPlayerValues(Dealer d, vector<Player*>&p){
  bool isBust;

  for(int i =0; i< p.size(); i++) {
    isBust = true;
    if( (p.at(i)->GetStatus()) == Status::DOUBLEDDOWN ||
        (p.at(i)->GetStatus()) == Status::HIT ||
        (p.at(i)->GetStatus()) == Status::INITIAL){
      for(int j = 0; j < Card::GetHandValues(p.at(i)->GetHand()).size(); j++){
        //cout<< "Checking Player "<< p.at(i)->GetID() << " hand value: " << Card::GetHandValues(p.at(i)->GetHand()).at(j)<< endl;
        if(Card::GetHandValues(p.at(i)->GetHand()).at(j)<=21){
          isBust = false;
          if(Card::GetHandValues(p.at(i)->GetHand()).at(j)==21){
            cout <<"\t\tPlayer " << p.at(i)->GetID() << " has BlackJack!\n";
            p.at(i)->SetStatus(Status::WAITING);
          }
        }
      }
      if (isBust){
        cout<<"\t\tPlayer "<< p.at(i)->GetID() << " busted\n";
        p.at(i)->SetStatus(Status::BUST);
      }
    }
  }
}

void BlackJack::PlayTWOTurn(Dealer d, vector<Player*> p){
  string input;
  for(int i=0; i< p.size(); i++){
    if(p.at(i)->GetStatus() != Status::WAITING && p.at(i)->GetStatus() != Status::LOWBALANCE){
      cout << "Player " << p.at(i)->GetID() << "'s Turn..."<< endl;
      cout << "Choose either: \"hit\" \"double down\" \"fold\" \"stay\"" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> input;
      while (
        !(input == "fold" && !(input == "double") && !(input == "hit") && !(input == "stay")||
        !(input == "fold") && input == "double" && p.at(i)->GetBalance() >= p.at(i)->GetAnte() && !(input == "hit") && !(input == "stay")||
        !(input == "fold") && !(input == "double") && input == "hit" && !(input == "stay")||
        !(input == "fold") && !(input == "double") && !(input == "hit") && input == "stay")
      ) {
        if(input == "double"){ cout << "Your balance is too low to double down" << endl;}
        cout << "Choose either: \"hit\" \"double down\" \"fold\" \"stay\"" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> input;

      }
      if (input[0] == 'd'){
        p.at(i)->AddAnte(p.at(i)->GetAnte());
        d.DealFromDeck(*p.at(i));
        p.at(i)->SetStatus(Status::DOUBLEDDOWN);
      }
      else if (input[0] == 'f'){
        p.at(i)->fold();
      }
      else if (input[0] == 'h'){
        d.DealFromDeck(*p.at(i));
        p.at(i)->SetStatus(Status::HIT);
        // cout<< "Play TWO turn: "
        // <<"status set " << endl;
      }
      else {
        p.at(i)->SetStatus(Status::STAY);
      }
    }
  }
}

bool BlackJack::AllPlayersFinished(vector<Player*> p){
  bool ret = true;
  // Checking if all players have gone..
  for(int i = 0; i<p.size(); i++){
    if(p.at(i)->GetStatus() == Status::HIT){ret = false;}
  }
  return ret;
}

void BlackJack::PlayNextTurn(Dealer d,vector<Player*> p){
  string input;
  for(int i = 0; i < p.size(); i++){
    if( p.at(i)->GetStatus() == Status::HIT){
      cout << "Player " << p.at(i)->GetID() << "'s Turn..."<< endl;
      cout << "Choose either: \"hit\" \"stay\"" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> input;
      while ( !( (input == "hit")^(input == "stay") ) ){
        cout << "Choose either: \"hit\" \"stay\"" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> input;
      }
      if (input[0] == 'h'){
        d.DealFromDeck(*p.at(i));
        p.at(i)->SetStatus(Status::HIT);
        // cout<< "Play next turn: "
        // <<"status set" << endl;
      }
      else {
        p.at(i)->SetStatus(Status::STAY);
      }
    }
  }
}

bool BlackJack::DealerFinished(Dealer d){
    return Card::GetHandValues(d.GetHand()).at(0) >= 17 ? true:false;

}
void BlackJack::FinishDealer(Dealer& d){
  d.DealFromDeck(d);
  cout<< "\t\tDealer getting card" << endl;
}

void BlackJack::FinalPayout(Dealer d, vector<Player*> p){
  int dBest = Card::GetHandValues(d.GetHand()).at(0);
  int pBest;

  for(int i = 0; i < p.size(); i++){
    if(p.at(i)->GetStatus()!=Status::BUST && p.at(i)->GetStatus()!=Status::FOLD && p.at(i)->GetStatus()!=Status::LOWBALANCE){
      for(int j = 0; j < Card::GetHandValues(p.at(i)->GetHand()).size(); j++){
        if(Card::GetHandValues(p.at(i)->GetHand()).at(j)<=21){
          pBest = Card::GetHandValues(p.at(i)->GetHand()).at(j);
          break;
        }
      }

      if(dBest < 21 && pBest < 21){ // dealer < 21, branch 1
        if(pBest>dBest){
          // cout << "Branch 1: " << endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has <21.("<<pBest<<") Player " << p.at(i)->GetID() << " is closer to 21.("<<dBest<<")\n";
          p.at(i)->AddAnteToBalanceRegularWin();
          p.at(i)->SetStatus(Status::WIN);
        }
        else if(pBest<dBest){
          // cout << "Branch 1: " << endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has <21.("<<pBest<<") Dealer closer to 21.("<<dBest<<")\n";
          p.at(i)->SetAnte(0); p.at(i)->SetStatus(Status::LOSE);
        }
        else {
          // cout << "Branch 1: " << endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has <21.("<<pBest<<") Dealer tie.("<<dBest<<")\n";
          p.at(i)->RemoveAnte(p.at(i)->GetAnte());
          p.at(i)->SetStatus(Status::TIE);
        }
      }
      else if (dBest > 21 && pBest <= 21){ //dealer > 21, branch 2
        if(pBest == 21){
          // cout << "Branch 2: " << endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has BlackJack.("<<pBest<<") Dealer bust.("<<dBest<<")\n";
          p.at(i)->AddAnteToBalanceBlackJackWin();
          p.at(i)->SetStatus(Status::WIN);
        }
        else{
          // cout << "Branch 2: " << endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has <21.("<<pBest<<") Dealer bust.("<<dBest<<")\n";
          p.at(i)->AddAnteToBalanceRegularWin(); p.at(i)->SetStatus(Status::WIN);
        }
      }
      else {    // dealer == 21, branch 3
        if(pBest == 21 && dBest != 21){
          // cout << "Branch 3: "<< endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has blackjack.("<<pBest<<") Dealer has no blackjack.("<<dBest<<")\n";
          p.at(i)->AddAnteToBalanceBlackJackWin();
          p.at(i)->SetStatus(Status::WIN);
        }
        else if(pBest == 21 && dBest == 21){
          // cout << "Branch 3: "<< endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has blackjack.("<<pBest<<") Dealer has blackjack.("<<dBest<<")\n";
          p.at(i)->SetStatus(Status::TIE);
          p.at(i)->RemoveAnte(p.at(i)->GetAnte());
        }
        else if(pBest < 21 && dBest == 21){
          // cout << "Branch 3: " << endl;
          cout << "\t\tPlayer " << p.at(i)->GetID() << " has <21.("<<pBest<<") Dealer has blackjack.("<<dBest<<")\n";
          p.at(i)->SetStatus(Status::LOSE);
          p.at(i)->SetAnte(0); p.at(i)->SetStatus(Status::LOSE);
        }
      }
    }
    else {p.at(i)->SetAnte(0);}
  }
}
void BlackJack::CleanGame(Dealer &d, vector<Player*> &p){
  d.ResetShuffleDeck();
  d.ClearHand();
  //clean players
  for(int i = 0; i < p.size(); i++){
    //cout<< "cleaning player"<< endl;
    p.at(i)->ClearHand();
    if(p.at(i)->GetStatus() != Status::LOWBALANCE){p.at(i)->SetStatus(Status::INITIAL);}
  }
  cout << "\t\tCREATING NEW GAME - CLEANING TABLE"<<endl;
}

bool BlackJack::PlayersHaveBalance(vector<Player*> p) {
  bool haveBalance = false;
  for(int i = 0; i < p.size(); i++){
    if(p.at(i)->GetBalance() >= double(MINIMUM_BET)){haveBalance = true; break;}
  }
  return haveBalance;
}

double BlackJack::GetStartingBalance(){
  string _input;
  double startingBalance;

  cout << "Please set the initial balance of all players. (Minimum is " << MINIMUM_BET << ")" << endl;
  cin >> _input;
  while (atof(_input.c_str()) < MINIMUM_BET){
    cout << "Please choose a number greater than or equal to " << MINIMUM_BET << endl;
    cin >> _input;
  }
  startingBalance = atof(_input.c_str());
  return startingBalance;
}

bool BlackJack::StartNewGame(){
  bool newGame = false;
  char _c;

  cout << "\t\tALL PLAYERS HAVE LOW BALANCE... THE HOUSE ALWAYS WINS!\n";
  cout << "Would you like to start a new game? Enter 'y' for yes or 'n' for no..." << endl;

  _c = getchar();
  while (_c != 'y' && _c!='n'){
    cout << "Please enter 'y' for yes or 'n' for no." << endl;
    _c = getchar();
  }

  if(_c == 'y'){newGame = true;}

  return newGame;
}