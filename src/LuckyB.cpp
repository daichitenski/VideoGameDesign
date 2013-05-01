#include "headers/LuckyB.h"

int main(int argc, char** argv){ //RM removed arguements since we aren't passing any to get rid of compiler warning
		MainMenu *mainState = new MainMenu();
		MainMenu *secondState = new MainMenu();
		secondState->setName("second");
		cout << "mainstate loaded" << endl;
		luckyB = new StateBasedGame(mainState);
		luckyB->addState(secondState);
		cout << "state added and state game created" << endl;
		luckyB->start();
		cout << "after start" << endl;
		
		/*Game lucky_B; //why not call it what it is?
		lucky_B.init();
		lucky_B.run();
		lucky_B.end();*/
	return 0;
}