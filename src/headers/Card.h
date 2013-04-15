#ifndef CARD_H
#define CARD_H

#include "cards.h"

using namespace std;

class Card{
	int value;
	bool faceUp;
	bool special;
	bool selected;

public:
	Card();
	Card(int newVal, bool facing);
	int getValue() const;
	bool isSpecial();
	bool isSelected();
	void flipCard();
	void setFacing(bool newFacing);
	void outputCard();
	void toggleSelected();
};

bool compare(Card a, Card b);

#endif