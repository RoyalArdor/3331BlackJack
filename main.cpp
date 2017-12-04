#include <iostream>
#include <vector>
#include "user.h"
#include "player.h"
#include "dealer.h"
#include "card.h"
#include <string>
#include <algorithm>
#define MINIMUM_BET 5
#define MAXIMUM_BET 100
using namespace std;

vector<Player*> players;
Player *playerTurn;
Dealer dealer;

void PrintIntro(){
  cout << " ====================\n"
    <<    "|Welcome to Blackjack|\n"
    <<    " ====================" << endl;
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
    //cout << "creating player " << i+1 << endl;
    Player* temp = new Player(i+1);
    _p.push_back(temp);
  }
  // cout << "players set, size: " << _p.size() << endl;
  return _p;
}

void DealInitial(Dealer &d, vector<Player*> &p){
  //cout<< "dealing two cards" << endl;
  for(int i=0; i<2; i++){
    // cout<< "dealing card to dealer\n";
    dealer.DealFromDeck(d);
    // cout <<"size of player vector: " << p.size() << endl;
    for (int j=0; j< static_cast<int>(p.size()); j++){
      // cout<< "dealing card to player\n";
      dealer.DealFromDeck(*p.at(j));
    }
  }
  Card::FlipCard(dealer.GetCard(0));
}

void PrintTable(Dealer &d, vector<Player*> &p){
  cout << "PLAYER\t\tCARDS" << endl
    <<    "------\t\t-----"<<endl;
  cout << "Dealer: \t";
  for(int i=0; i< d.GetHand().size(); i++){
    cout << d.GetHand().at(i) << ", ";
  }
  cout << "= [";
  for(int j=0; j< Card::GetHandValues(d.GetHand()).size(); j++){
    cout << Card::GetHandValues(d.GetHand()).at(j)<< ",";
  }
  cout << "]";
  cout << endl;

  for(int i=0; i< p.size(); i++){
    cout << "Player " << i+1 << ":\t";
    for(int j=0; j< p.at(i)->GetHand().size(); j++){
      cout << p.at(i)->GetHand().at(j) << ", ";
    }
    cout << "= [";
    for(int j=0; j< Card::GetHandValues(p.at(i)->GetHand()).size(); j++){
      cout << Card::GetHandValues(p.at(i)->GetHand()).at(j)<< ",";
    }
    cout << "]";
    cout << "\t\tBalance: $ " << p.at(i)->GetBalance();
    cout << "\tStatus: ";
    switch(p.at(i)->GetStatus()) {
      case Status::BUST:  cout << "BUST";
                          break;
      case Status::WAITING:   cout << "WAITING FOR DEALER";
                          break;
      case Status::DOUBLEDDOWN:
                          cout << "DOUBLEDDOWNED";
                          break;
      case Status::HIT:   cout << "HIT";
                          break;
      case Status::STAY:  cout << "STAY";
                          break;
      case Status::FOLD:  cout << "FOLD";
                          break;
      case Status::INITIAL: cout << "";
                            break;  
      case Status::WIN: cout << "WIN";
                            break;  
      case Status::LOSE: cout << "LOSE";
                            break;  
      case Status::TIE: cout << "TIE";
                            break;                    
      default: cout << "";
    }
    cout << endl;
  }
}

void PlaceBets(Player *p, vector<Player*> &_players){
  string _input;
  p = _players[0];
  cout << "Betting Phase..."<< endl;
  for(int i = 0; i< _players.size(); i++){
    cout << "Player " << p->GetID() << "'s turn\n"
      << "Place your bet ($" << MINIMUM_BET << " to $" << MAXIMUM_BET <<")"<< endl;
    cin >> _input;
    if(p->GetBalance()>=5.00){ //check balance

      while(atof(_input.c_str()) < 5.0 || atof(_input.c_str()) > 100.0){  //ensure balance in range for bet
        cout << "type an amount from $" << MINIMUM_BET << " to $" << MAXIMUM_BET <<"."<< endl;
        cin >> _input;
      }

      p->AddAnte(atof(_input.c_str()));
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

//Check every player's hand whether they win or bust
void CheckPlayerValues(Dealer d, vector<Player*>&p){
  bool isBust = true;

  for(int i =0; i< p.size(); i++) {
    if( (p.at(i)->GetStatus()) == Status::DOUBLEDDOWN ||
        (p.at(i)->GetStatus()) == Status::HIT ||
        (p.at(i)->GetStatus()) == Status::INITIAL){
      for(int j = 0; j< Card::GetHandValues(p.at(i)->GetHand()).size(); j++){
        // cout<< "Checking hand value: " << Card::GetHandValues(p.at(i)->GetHand()).at(j)<< endl; 
        if(Card::GetHandValues(p.at(i)->GetHand()).at(j)<=21){
          isBust = false;
          if(Card::GetHandValues(p.at(i)->GetHand()).at(j)==21){
            cout <<"Player " << p.at(i)->GetID() << " has BlackJack!\n";
            p.at(i)->SetStatus(Status::WAITING);
          }
        }
      }
      if (isBust){
        cout<<"Player "<< p.at(i)->GetID() << " busted\n";
        p.at(i)->SetStatus(Status::BUST);
      }
    }
  }
}

void PlayTWOTurn(Dealer d, vector<Player*> p){
  string input;
  for(int i=0; i< p.size(); i++){
    if(p.at(i)->GetStatus() != Status::WAITING){
      cout << "Player " << p.at(i)->GetID() << "'s Turn..."<< endl;
      cout << "Choose either: \"hit\" \"double down\" \"fold\" \"stay\"" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cin >> input;
      while (
        !(input == "fold" && !(input == "double") && !(input == "hit") && !(input == "stay")||
        !(input == "fold") && input == "double" && !(input == "hit") && !(input == "stay")||
        !(input == "fold") && !(input == "double") && input == "hit" && !(input == "stay")||
        !(input == "fold") && !(input == "double") && !(input == "hit") && input == "stay")
      ) {
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

bool AllPlayersFinished(vector<Player*> p){
  bool ret = true;
  //cout << "Checking if all players have gone.." << endl;
  for(int i = 0; i<p.size();i++){
    if(p.at(i)->GetStatus() == Status::HIT){ret = false;}
  }
  return ret;
}

void PlayNextTurn(Dealer d,vector<Player*> p){
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

bool DealerFinished(Dealer d){
    return Card::GetHandValues(d.GetHand()).at(0) >= 17 ? true:false;
    
}
void FinishDealer(Dealer& d){
  d.DealFromDeck(d);
}

void FinalPayout(Dealer d, vector<Player*> p){
  int dealersBest = Card::GetHandValues(d.GetHand()).at(0);
  int pBest;
  int pDelta;
  for(int i = 0; i < p.size(); i++){
    if(p.at(i)->GetStatus()!=Status::BUST){
      for(int j = 0; j < Card::GetHandValues(p.at(i)->GetHand()).size(); j++){
        pDelta = 21 - Card::GetHandValues(p.at(i)->GetHand()).at(j) ;
        if(dealersBest<21 ){
          if(pDelta>0){
            pBest = Card::GetHandValues(p.at(i)->GetHand()).at(j);
            if(pBest>dealersBest){
              p.at(i)->AddAnteToBalanceRegularWin();
              p.at(i)->SetStatus(Status::WIN);
              cout<< "branch1: i dont have 21 - win" << endl;
            }
            else if(pBest<dealersBest){
              p.at(i)->SetAnte(0); p.at(i)->SetStatus(Status::LOSE);
              cout<< "branch1: i dont have 21 - lose" << endl;
            }
            else {
              p.at(i)->RemoveAnte(p.at(i)->GetAnte());
              p.at(i)->SetStatus(Status::TIE);
              cout<< "branch1: i dont have 21 - tie" << endl;
            }
            break;
          }
        }
        else{
          cout<< "branch2: i dont have 21 - dealer bust" << endl;
          p.at(i)->AddAnteToBalanceRegularWin(); p.at(i)->SetStatus(Status::WIN);
          break;
        }
      }

      if(p.at(i)->GetStatus() == Status::WAITING && dealersBest!=21){
        cout<< "branch3: i have 21 - win" << endl;
        p.at(i)->AddAnteToBalanceBlackJackWin();
        p.at(i)->SetStatus(Status::WIN);
      }
      else if(p.at(i)->GetStatus() == Status::WAITING && dealersBest == 21){
        cout<< "branch3: i have 21 - tie" << endl;
        p.at(i)->SetStatus(Status::TIE);
        p.at(i)->RemoveAnte(p.at(i)->GetAnte());
      }
    }
    else {p.at(i)->SetAnte(0);}
  }
}
void CleanGame(Dealer &d, vector<Player*> p){
  d.ResetShuffleDeck();
  d.ClearHand();
  //clean players
  for(int i = 0; i < p.size(); i++){
    //cout<< "cleaning player"<< endl;
    p.at(i)->ClearHand();
    p.at(i)->SetStatus(Status::INITIAL);  
  }
}
int main(){
  PrintIntro();
  SetPlayers(players);
  while(players.size()>0){
    PlaceBets(playerTurn, players);
    DealInitial(dealer, players);
    CheckPlayerValues(dealer, players);
    PrintTable(dealer, players);
    PlayTWOTurn(dealer, players);
    CheckPlayerValues(dealer, players);
    PrintTable(dealer, players);
    CheckPlayerValues(dealer, players);
    PrintTable(dealer, players);
    //wait for all players to finish hit/stay rounds
    while(!AllPlayersFinished(players)){
      PlayNextTurn(dealer, players);
      CheckPlayerValues(dealer, players);
      PrintTable(dealer, players);
    }
    //flip dealer first card
    Card::FlipCard(dealer.GetCard(0));
    //dealer finish deck and reveal
    while(!DealerFinished(dealer)){
      FinishDealer(dealer);
      PrintTable(dealer, players);
    }

    FinalPayout (dealer, players);
    PrintTable (dealer, players);
    CleanGame (dealer, players);
  }
  system("Pause");
}