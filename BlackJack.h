#ifndef BLACKJACK_H
#define BLACKJACK_H
#include "BlackJack.h"
#include <iostream>
#include <vector>
#include "User.h"
#include "Player.h"
#include "Dealer.h"
#include "Card.h"
#include <string>
#include <algorithm>
class BlackJack{
public:
  static void PrintIntro();
  static void SetPlayers(vector<Player*> &, double);

  static void DealInitial(Dealer &, vector<Player*> &);

  static void PrintTable(Dealer &, vector<Player*> &);

  static void PlaceBets(vector<Player*> &);

  static bool PlayersHaveBalance(vector<Player*>);

  //Check every player's hand whether they win or bust
  static void CheckPlayerValues(Dealer , vector<Player*> &);

  static void PlayTWOTurn(Dealer , vector<Player*> );

  static bool AllPlayersFinished(vector<Player*> );

  static void PlayNextTurn(Dealer ,vector<Player*> );

  static bool DealerFinished(Dealer );
  static void FinishDealer(Dealer& );

  static void FinalPayout(Dealer , vector<Player*> );
  static void CleanGame(Dealer &, vector<Player*> &);

  static double GetStartingBalance();

  static bool StartNewGame();
};
#endif
