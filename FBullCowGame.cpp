#pragma once
#include "FBullCowGame.h"
//test
FBullCowGame::FBullCowGame()
{
	Difficulty = SetDifficutly();
	BuildWord();
	ResetAttempts();
}

void FBullCowGame::SetGameOn(bool PlayAgain) { GameOn = PlayAgain; }

int32 FBullCowGame::GetMaxTries() const
{

	TMap<int32, int32> WordLengthToMaxTries{
		{3, 3},
		{4, 7},
		{5, 10},
		{6, 16}
	};
	return WordLengthToMaxTries[MagicWord.length()];
}

bool FBullCowGame::bGetGameOn() const { return GameOn; }
int32 FBullCowGame::GetAttempts() const { return Attempts; }

FString FBullCowGame::GetMagicWord() const
{
	return MagicWord;
}

int32 FBullCowGame::SetDifficutly()
{
	int32 difficulty = 1;
	std::cout << "\n\nHow difficult do you want the game to be?";
	std::cout << "\n1 = Easy\n2 = Medium\n3 = Hard\n4 = Extreme!\n";
	std::cin >> difficulty;
	std::cin.ignore();
	return difficulty;
}

void FBullCowGame::RunGame()
{
	while (Attempts > 0) 
	{
		GetGuess();
		if (Guess.compare(MagicWord) != 0)
		{
			FBullCowCount BC = GetBullsCows(Guess);
			SubtractAttempt();
			//TODO substitute for return values
			std::cout << "Incorrect Guess Sorry";
			std::cout << "\nBulls: " << BC.Bulls << "\nCows: " << BC.Cows;
			std::cout << std::endl;
			std::cout << "\nYou have " << Attempts << " guesses remaining\n";
		}
		else
		{
			//TODO substitute for return values
			std::cout << "\nThat is correct, the word was " << MagicWord << "!";
			std::cout << std::endl;
			return;
		}
	}
	std::cout << "\nYou ran out of guesses sorry\n";
}

void FBullCowGame::SubtractAttempt() 
{ 
	Attempts--; 
}

void FBullCowGame::ResetAttempts() 
{
	Attempts = GetMaxTries();
}

bool FBullCowGame::bIsIsogram(FString Word) const
{
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

void FBullCowGame::GetGuess()
{
	bool GettingGuess = true;
	FString ThisGuess = "";
	while (GettingGuess == true) {

		std::cout << "Enter your guess: ";
		getline(std::cin, ThisGuess);
		EWordStatus ValidGuess = CheckValidity(ThisGuess);

		switch (ValidGuess) {
		case EWordStatus::Bad_Characters:
			std::cout << "You have entered some bad characers\n";
			std::cout << "We don't accept: " << Bad_Characters;
			std::cout << std::endl;
			std::cout << std::endl;
			break;

		case EWordStatus::Wrong_length:
			std::cout << "Sorry that word is not the correct length\n";
			std::cout << "It needs to be " << MagicWord.length() << " letters long\n";
			std::cout << std::endl;
			break;
		
		case EWordStatus::Not_Isogram:
			std::cout << "That's not an Isogram which is OK\n";

		case EWordStatus::OK:
			Guess = ConvertToLower(ThisGuess);
			GettingGuess = false;
			break;
		
		default:
			break;
		}
	}
}

void FBullCowGame::PrintGameSummary()
{
	if (Attempts == 0) {
		std::cout << "\nGame Summary: \n\n";
		std::cout << "Final Guess Bulls: " << BC.Bulls << "\n";
		std::cout << "Final Guess Cows: " << BC.Cows << "\n";
		std::cout << "Guesses used: " << GetMaxTries() << "\n";
	}
	else {
		std::cout << "It took you " << GetMaxTries() - Attempts << " guesses to get it correct";
	}
}

FString FBullCowGame::ConvertToLower(FString Word)
{
	FString Converted_Word = "";
	for (int32 i = 0; i < Word.length(); i++) {
		Converted_Word += tolower(Word[i]);
	}
	return Converted_Word;
}

void FBullCowGame::PrintIntro()
{
	// introduce the game
	
std::cout << "                          ..---.							\n";
std::cout << "                         // |\\||\\							\n";
std::cout << "  \\   /                 ///;||\\|;\\               \\   /	\n";
std::cout << "    o               .__// \\\____//\\_,.              o		\n";
std::cout << "  /   \\              Y{_\\_/  \\'' = __/           /   \\	\n";
std::cout << "                     \\___   (o) (o)  }					\n";
std::cout << "                       /         :--'    MOO!				\n";
std::cout << "                  .---/ \\_    `__\\-.						\n";
std::cout << "                 /     `--\\___(o'o) \\					\n";
std::cout << "          \\   / |     \\      `===='  |\\   /				\n";
std::cout << "            o    `.    `.    .'    .'   o					\n";
std::cout << "          /   \\   (`.    `. '    .')  /   \\				\n";
std::cout << "                  (  `.    `...'   )						\n";
std::cout << "                  (   .+.    `-.   )						\n";
std::cout << "                  (.-'  .>-._   `-.)						\n";
std::cout << "  \\   /           (___.-'      `-.___)            \\   /	\n";
std::cout << "    o              (                )               o		\n";
std::cout << "  /   \\            (                )             /   \\	\n";
	std::cout << "Welcome to Bulls and Cows, a fun word game!" << std::endl;
	std::cout << "Can you guess the " << MagicWord.length();
	std::cout << " letter word I'm thinking of?\n";
	if (Difficulty = 4) {
		std::cout << "You chose extreme difficulty, the word is not an isogram (has repeating letters)\n";
	}
	std::cout << std::endl;
	return;
}

void FBullCowGame::BuildWord()
{
	//TODO: Build word based on random dictonary word
	switch (Difficulty) {
	case 1:
		MagicWord = "pop";
	case 2:
		MagicWord = "copy";
	case 3:
		MagicWord = "ready";
	case 4:
		MagicWord = "status";
	}
}

bool FBullCowGame::bAskToPlayAgain()
{
	FString Input = "";
	std::cout << std::endl;
	std::cout << "You want to play again fella? ";
	getline(std::cin, Input);
	std::cout << std::endl;
	std::transform(Input.begin(), Input.end(), Input.begin(), ::tolower);
	if (Input.compare("yes") == 0 || Input[0] == 'y')
	{
		ResetAttempts();
		return true;
	}
	else
	{
		return false;
	}
}

EWordStatus FBullCowGame::CheckValidity(FString ThisGuess)
{
	bool Bad_Character = false;
	Bad_Characters = "";
	for (int32 n = 0; n < ThisGuess.length(); n++) {
		int Upper_Char = toupper(ThisGuess[n]);
		if (Upper_Char < 'A' || Upper_Char > 'Z') {
			Bad_Character = true;
			Bad_Characters += ThisGuess[n];
		}
	}

	if (Bad_Character == true){
		return EWordStatus::Bad_Characters;
	}

	else if (ThisGuess.length() != MagicWord.length()) {
		return EWordStatus::Wrong_length;
	}

	else if (bIsIsogram(ThisGuess) == false) {
		return EWordStatus::Not_Isogram;
	}

	else return EWordStatus::OK;
}
FBullCowCount FBullCowGame::GetBullsCows(FString){
	BC.Bulls = 0;
	BC.Cows = 0;
	FString MagicTemp = MagicWord;
	FString GuessTemp = Guess;
	//Loop through every letter in guess
	for (int32 j = 0; j < Guess.length(); j++) {
		//First see if letter matches, which gets a cow
		if (GuessTemp[j] == MagicWord[j]) {
			BC.Cows++;
		}
		//Then loop through the magic word letters, remove the letter on match
		for (int32 i = 0; i < MagicTemp.length(); i++) {
			if (GuessTemp[j] == MagicTemp[i]) {
				BC.Bulls++;
				MagicTemp.erase(i,i);
			}
		}
	}
	return BC;

}


