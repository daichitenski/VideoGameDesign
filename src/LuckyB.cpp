#include "headers/LuckyB.h"

int main(int argc, char** argv){ //RM removed arguements since we aren't passing any to get rid of compiler warning
		Game lucky_B; 
		lucky_B.init();
		lucky_B.run();
		lucky_B.end();
	return 0;
}