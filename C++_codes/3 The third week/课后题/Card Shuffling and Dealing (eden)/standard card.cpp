#include "card.hpp"
#include <string>

Card::Card(int cardFace, int cardSuit) {
  face = (cardFace >= 0 && cardFace < totalFaces) ? cardFace : 0;
  suit = (cardSuit >= 0 && cardSuit < totalSuits) ? cardSuit : 0;
}

std::string Card::toString() const {
  return std::string(faceNames[face]) + " of " + std::string(suitNames[suit]);
}

int Card::getFace() const { return face; }
int Card::getSuit() const { return suit; }

const char* Card::faceNames[totalFaces] =
  { "Ace", "Deuce", "Three", "Four", "Five", "Six",
    "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };
const char* Card::suitNames[totalSuits] =
  { "Hearts", "Diamonds", "Clubs", "Spades" };
