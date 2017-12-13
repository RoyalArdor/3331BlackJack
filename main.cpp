#include <iostream>
#include <vector>
#include "User.h"
#include "Player.h"
#include "Dealer.h"
#include "Card.h"
#include "BlackJack.h"
#include <string>
#include <algorithm>


using namespace std;

vector<Player*> players;
Dealer dealer;

int main(){
    do {
        players.clear();
        BlackJack::PrintIntro();
        BlackJack::SetPlayers(players, BlackJack::GetStartingBalance());
        while( BlackJack::PlayersHaveBalance(players)){
            BlackJack::PlaceBets(players);
            BlackJack::DealInitial(dealer, players);
            BlackJack::CheckPlayerValues(dealer, players);
            BlackJack::PrintTable(dealer, players);
            BlackJack::PlayTWOTurn(dealer, players);
            BlackJack::CheckPlayerValues(dealer, players);
            BlackJack::PrintTable(dealer, players);
            //wait for all players to finish hit/stay rounds
            while(!BlackJack::AllPlayersFinished(players)){
                BlackJack::PlayNextTurn(dealer, players);
                BlackJack::CheckPlayerValues(dealer, players);
                BlackJack::PrintTable(dealer, players);
            }
            //flip dealer first card
            Card::FlipCard(dealer.GetCard(0));
            cout<< "\t\tDealer card flipped" << endl;
            //dealer finish deck and reveal
            while(!BlackJack::DealerFinished(dealer)){
                BlackJack::FinishDealer(dealer);
                BlackJack::PrintTable(dealer, players);
            }

            BlackJack::FinalPayout (dealer, players);
            BlackJack::PrintTable (dealer, players);
            BlackJack::CleanGame (dealer, players);
        }
    }
    while(BlackJack::StartNewGame());
}
