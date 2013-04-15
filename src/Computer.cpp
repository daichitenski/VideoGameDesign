#include "headers/Computer.h"

	void Computer::play(Deck &d, Discard &dis)
	{
		unsigned int i=0,j;
		int sp2 = -1, sp10 = -1;
		//vector<Card> ha = h.getHand();
		while(i < h.handList.size() && h.handList[i].getValue() < dis.getTopCardValue()  ) i++;
		for(j=0; j<h.handList.size(); j++)
			if(h.handList[j].getValue() == 2-1) sp2 == j;
			else if (h.handList[j].getValue() == 10-1) sp10 == j;

		 if(i < h.handList.size())
			for(j=i; j<h.handList.size(); j++)//perhaps only let loop for the max number of cards for any value
				if(h.handList[j].getValue() == dis.getTopCardValue())
					if(h.handList[j].isSelected() == false)
						h.handList[j].toggleSelected();
				else if(h.handList[j].getValue() == h.handList[i].getValue())
					if(h.handList[j].isSelected() == false)
						h.handList[j].toggleSelected();
		else
		{
			if(sp10 > -1)
				if(h.handList[sp10].isSelected() == false)
					h.handList[sp10].toggleSelected();
			else if (sp2 > -1)
				if(h.handList[sp2].isSelected() == false)
				{
					h.handList[sp2].toggleSelected();
					int small = h.handList[0].getValue();
					int smallPos = -1;
					for(j=0; j<h.handList.size(); j++)//Get the smallest value in the hand
						if(h.handList[j].getValue() < small)
						{
							small = h.handList[j].getValue();
							smallPos = j;
						}
					if(smallPos > -1)
						for(j=smallPos; j<h.handList.size(); j++)
							if(h.handList[j].getValue() == small)
								if(h.handList[j].isSelected() == false)
									h.handList[j].toggleSelected();
				}
				else //Have to pick up the discard pile
				{
					for(j=0; j < dis.discardPile.size(); j++)
						h.insert(dis.discardPile[j]);
					dis.discardPile.clear();
				}
		}		
		while(h.getNumCards() < maxHand)
			h.drawFromDeck(&d);
	}