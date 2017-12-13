# 3331BlackJack
COP 3331 Final Project: BlackJack, Project specifications:

Implement a computer Blackjack game. The computer program is the dealer and provides
interface for user to play. The following rules should be implemented and the game
should follow the dealing routine as defined.

Blackjack rules:
  1. User’s initial balance -- $1000
  2. Minimum bet – $5 and maximum bet -- $100
  3. Multiple players – as many as 5
  4. Win – closer to 21 than the dealer (computer) without going over 21
  5. Player’s cards are all face up (shown to all players and the computer)
  6. Dealer’s first card is face down, the rest are face up
  7. An Ace can count as either 1 or 11
  8. The cards from 2 through 9 are valued at their face value
  9. The 10, Jack, Queen, and King are all valued at 10
  10. The value of a hand is simply the sum of the point counts of each card in the
       hand, For example, a hand containing (5,7,9) has the value of 21
  11. The dealer must continue to take cards ("hit") until his total is 17 or greater
  12. Blackjack rule: A blackjack, or natural, is a total of 21 in your first two cards. A
       winning blackjack pays the player odds of 3 to 2. A player blackjack beats any
       dealer total other than blackjack, including a dealer's three or more card 21. If
       both a player and the dealer have blackjack, the hand is a tie or push.
  13. The player has the option to either draw another card to the hand ("hit"), or stop at
       the current total ("stand").
  14. When the player has two cards, the player can “double down". Doubling down
       allows the player to double his/her bet and receive one, and only one, additional
       card to the hand.
  15. When the player has two cards, the player can “surrender”, which offers the
       choice to fold the player’s hand, at the cost of half of the original bet. The player
       must make that decision prior to taking any other action on the hand
  16. When the player is dealt a matching pair of cards, you have the ability to split the
       hand into two separate hands, and play them independently. The rule allows a
       player to split up to 3 times, making 4 separate hands, with 4 separate bets.
       
Routine:
  1. Place bet
  2. Once all the bets are made, the dealer will deal the cards to the players. He'll make
     two passes around the table starting at his left (your right) so that the players and
     the dealer have two cards each
  3. The dealer will flip one of his cards over, exposing its value
  4. The players cards will be dealt face-up
  5. Once the cards are dealt play proceeds around the table, starting at the first seat to
      the dealer's left, also called first base. Each player in turn indicates to the dealer
      how he wishes to play the hand
  6. After each player has finished his hand, the dealer will complete his hand, and
      then pay or collect the player bets.
      
Your program should implement all the rules, provide interface for users to play, shuffle
cards, deal cards, compute who wins, take or pay the bet. 
