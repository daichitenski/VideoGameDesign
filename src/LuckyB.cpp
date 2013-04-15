#include "headers/LuckyB.h"

bool compare(Card a, Card b) 
{
	int tempa = a.getValue();
	int tempb = b.getValue();
	if(tempa == 0) tempa = 14;
	if(tempb == 0) tempb = 14;

	return (tempa > tempb);
}