#include "card.hpp"
const char* Card::faceNames[13]={"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
const char* Card::suitNames[4]={"Hearts", "Diamonds", "Clubs", "Spades"};
Card::Card(int cardFace, int cardSuit){
	face = cardFace;
	suit = cardSuit;
} // initialize face and suit
std::string Card::toString() const{
	std::string str, str1=faceNames[face], str2=suitNames[suit];
	std::string str3 = " of ";
	str = str1 + str3 +str2;
	return str;
} // returns a string representation

        // get the card's face
int Card::getFace() const{
	return face;
}

        // get the card's suit
int Card::getSuit() const{
	return suit;
}