#include "headers/Computer.h"

	void Computer::play(Deck &d, Discard &dis)
	{
		unsigned int j;
		int i = -1;
		int sp2 = -1, sp10 = -1;
		//while(i < h.handList.size() && h.handList[i].getValue() < dis.getTopCardValue()  ) i++; 
		if(h.getNumCards() > 0){
			for(j=0; j<h.handList.size(); j++)//Looks to see if there is a special card and if so where
				if(h.handList[j].getValue() == 2-1) sp2 == j;
				else if (h.handList[j].getValue() == 10-1) sp10 == j;
				else if(h.handList[i].getValue() >= dis.getTopCardValue() && i == -1) i = j; //Looks for a card that matches or more than discard pile
		
			 if(i>-1 && i < h.handList.size()){
				for(j=i; j<4*d.getNumDecks(); j++)//let loop for the max number of cards for any value
					if(h.handList[j].getValue() == dis.getTopCardValue())
						if(h.handList[j].isSelected() == false)
							h.handList[j].toggleSelected();
					else if(h.handList[j].getValue() == h.handList[i].getValue())
						if(h.handList[j].isSelected() == false)
							h.handList[j].toggleSelected();
			}
			else{
				if(sp10 > -1){
					if(h.handList[sp10].isSelected() == false)
						h.handList[sp10].toggleSelected();
				}
				else if (sp2 > -1){
					if(h.handList[sp2].isSelected() == false){
						h.handList[sp2].toggleSelected();
						int small = 15;
						int smallPos = -1;
						for(j=0; j<h.handList.size(); j++)//Get the smallest value in the hand
							if(h.handList[j].getValue() != 2-1 || h.handList[j].getValue() != 10-1)
								if(h.handList[j].getValue() < small){
									small = h.handList[j].getValue();
									smallPos = j;
								}
						if(smallPos > -1){
							for(j=smallPos; j<d.getNumDecks(); j++)
								if(h.handList[j].getValue() == small)
									if(h.handList[j].isSelected() == false)
										h.handList[j].toggleSelected();
						}
						else{
							//Plays off Board Hand or play all the 2's then the discard
							cout << "TO DO PLAY OFF THE BOARD HAND FOR COMPUTER" << endl;
						}
					}
					else{ //Have to pick up the discard pile
						for(j=0; j < dis.discardPile.size(); j++)
							h.insert(dis.discardPile[j]);
						dis.discardPile.clear();
					}
				}
			}		
			while(h.getNumCards() < maxHand && d.getNumCards() > 0)
				h.drawFromDeck(&d);
			h.sortHand();
		}
		else{
			//Play Board Hand
			cout << "Board Play yet to code" << endl;
		}
	}