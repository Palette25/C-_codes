include "deck-of-cards.hpp"
DeckOfCards::DeckOfCards(){
    for (unsigned int i(0); i <= 12; ++i)
    {
        for (unsigned int j(0); j <= 3; ++j)
        {
            Card card(i, j);
            deck.push_back(card);
        }
    }
    currentCard = 0;
}
// constructor initializes deck
Card DeckOfCards::dealCard(){
  int card_, current = currentCard;
  while(1){
  if(current<=12) {
    card_=current;
    break;}
  else current-=13;
 }
  Card card(card_, currentCard/13);
  currentCard++;
  return card;
 } // deals cards in deck
 bool DeckOfCards::moreCards() const{
  if(currentCard>=52) return 0;
  else return 1;
 }