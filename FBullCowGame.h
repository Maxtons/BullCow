#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus {
	OK,
	Not_Isogram,
	Wrong_length,
	Bad_Characters
};

class FBullCowGame{
public:

	FBullCowGame();

	int GetMaxTries() const;
	bool bGetGameOn() const;
	int GetAttempts() const;
	FString GetMagicWord() const;
	int32 SetDifficutly();
	void BuildWord();

	void GetGuess();
	void PrintGameSummary();
	FString ConvertToLower(FString);
	EWordStatus CheckValidity(FString);
	FBullCowCount GetBullsCows(FString);
	

	void PrintIntro();
	void SetGameOn(bool);
	void RunGame();
	bool bAskToPlayAgain();
	
	void SubtractAttempt();
	void ResetAttempts();


private:
	bool GameOn = true;
	int Attempts = GetMaxTries();
	int32 Difficulty;
	bool bIsIsogram(FString) const;
	FString MagicWord;
	FString Guess;
	FString Bad_Characters;
	FBullCowCount BC;
};