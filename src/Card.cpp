#include "headers/Card.h"

	Card::Card(){
		value = 0;
		special = false;
		faceUp = false;
		selected = false;
	}
	Card::Card(int newVal, bool facing){
		value = newVal;
		if(newVal == 2-1 || newVal == 10-1)
			special = true;
		else
			special = false;
		//image = newImage;
		faceUp = facing;
		selected=false;
	}
	int Card::getValue() const{
		return value;
	}
	int Card::getCardValue() const //return the numerical value of a playing card
	{
		if(value == 0) return 14;
		return value + 1;
	}
	bool Card::isSpecial(){
		return special;
	}
	bool Card::isSelected(){
		return selected;
	}
	void Card::flipCard(){
		faceUp = !faceUp;
	}
	void Card::setFacing(bool newFacing){
		faceUp = newFacing;
	}
	void Card::outputCard(){
		cout<<"Value: "<<value;
		cout<<" Special: " << special;
		if(faceUp)
			cout<<"  Face Up"<<endl;
		else
			cout<<"  Face Down"<<endl;
	}
	void Card::toggleSelected(){
		selected = !selected;
	}
	void Card::setSelect(bool a)
	{
		selected = a;
	}
	
	bool compare(Card a, Card b){
		int tempa = a.getValue();
		int tempb = b.getValue();
		//testing fix for aces
		if(tempa == 0) tempa = 13;
		if(tempb == 0) tempb = 13;

		return (tempa > tempb);
	}
	bool compare2(Card a, Card b){
		int tempa = a.getValue();
		int tempb = b.getValue();
		//testing fix for aces
		if(tempa == 0) tempa = 13;
		if(tempb == 0) tempb = 13;

		return (tempa < tempb);
	}