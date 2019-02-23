/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsivle for all
user interaction. For game logic see the FBullCowGame class.
*/


#include "FBullCowGame.h"

using FText = std::string;

int main() 
{
	FBullCowGame BCGame;
	BCGame.PrintIntro();
	while (BCGame.bGetGameOn() == true){	
		BCGame.RunGame();
		BCGame.SetGameOn(BCGame.bAskToPlayAgain());
	}
	BCGame.PrintGameSummary();
	std::cout << std::endl;
	std::cout << "Thanks for playing sir have a great day!\n\n";
	return 0;
}

////Methods///////

