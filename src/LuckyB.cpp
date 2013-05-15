#include "headers/LuckyB.h"

int main(int argc, char** argv){ 
		MainMenu *mainState = new MainMenu();
		Game *gameState = new Game();
		
		srand (time(NULL)); //seed srand timer
		
		luckyB = new StateBasedGame(mainState);
		luckyB->addState(gameState);
		luckyB->start();
		
		/*Game lucky_B; //why not call it what it is?
		lucky_B.init();
		lucky_B.run();
		lucky_B.end();*/
	return 0;
}