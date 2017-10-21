#include "deck-of-cards.hpp"
 
DeckOfCards::DeckOfCards() {
  currentCard = 0;
  for (int i = 0; i < Card::totalFaces * Card::totalSuits; ++i) {
    Card card(i % Card::totalFaces, i / Card::totalFaces);
    deck.push_back(card);
  }
}
 
Card DeckOfCards::dealCard() {
  return deck[currentCard++];
}
 
bool DeckOfCards::moreCards() const {
  return currentCard < deck.size();
}