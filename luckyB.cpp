#include <iostream> 
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <SDL/SDL.h>

using namespace std;

const int MAXRANGE = 13;

class cardClass 
{
private:
	int value;
	//int suit;
	bool special;
	bool faceUp;
public:
	cardClass()
	{
		//srand((unsigned)time(0));
		int randNum = rand()% MAXRANGE;
		if(randNum == 2 || randNum == 10)
		{
			special = true;
		}
		else
			special = false;
		value = randNum;
		faceUp = false;
	}
	cardClass(int v){
		if( v < 0 || v >= MAXRANGE)
		{
			if( v == MAXRANGE)
			{
				v --;
			}
			else
			{
				//srand((unsigned)time(0));
				v = rand()% MAXRANGE;
			}
		}
		if(v == 2 || v == 10)
		{
			special = true;
		}
		else
		{
			special = false;
		}
		value = v;
		faceUp = false;
	}
	//void setCard(int v);
	void flipCard(bool f){ faceUp = f;}
	int getCardValue(){return value;}
	//int getSuit();
	int getFaceUp(){return faceUp;}
	int getSpecial(){return special;}
};

int main(int argc, char **argv)
{
	cardClass c1, c2(1), c3(13), c4(20), c5(2);
	srand((unsigned)time(0));
	
	cout << c2.getCardValue() << " " << c2.getFaceUp() << " " << c2.getSpecial() << endl;
	cout << c3.getCardValue() << " " << c3.getFaceUp() << " " << c3.getSpecial() << endl;
	cout << c4.getCardValue() << " " << c4.getFaceUp() << " " << c4.getSpecial() << endl;
	cout << c5.getCardValue() << " " << c5.getFaceUp() << " " << c5.getSpecial() << endl;
	cout << c1.getCardValue() << " " << c1.getFaceUp() << " " << c1.getSpecial() << endl;

	return 0;
}