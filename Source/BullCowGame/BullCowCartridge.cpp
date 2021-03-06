// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

//Require if we load word list from .txt file from file path
//#include "Misc/FileHelper.h"
//#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    //Code to load word list from .txt file
    //const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    //FFileHelper::LoadFileToStringArray(Words, *WordListPath);
    Isograms = GetValidWords(Words);
    SetupGame();  
}

void UBullCowCartridge::OnInput(const FString& PlayerInput) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput);
    }
}

void UBullCowCartridge::SetupGame()
{
    //Welcome message to Player

    PrintLine(TEXT("Welcome to BullCow Game!!!"));

    int32 MaxRange = Isograms.Num() -1;
    int32 RandomIndex = FMath::RandRange(0, MaxRange);
    HiddenWord = Isograms[RandomIndex];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess a %i letter word !"), HiddenWord.Len()); //Will be replaced by Magic Number

    //PrintLine(TEXT("The HiddenWord is : %s."),*HiddenWord);   
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("HINT: The Isogram begins from the letter: \'%c\'"), HiddenWord[0]);
    PrintLine(TEXT("Type in a word and \npress 'Enter' key to continue : "));
    //Array of Characters
    // const TCHAR HW[] = TEXT("plums");
    // PrintLine(TEXT("Character 1 of the hidden word is : %c"), HiddenWord[0]);
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;

    PrintLine(TEXT("\nPlease, press Enter key to play again!"));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (HiddenWord == Guess)
    {
        PrintLine(TEXT("You have Won!"));
        EndGame();
        return;
    }

    //Checks Right Number of Characters
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("The hidden word is %i letters long."), HiddenWord.Len());
        PrintLine(TEXT("Sorry, try guessing again! \nYou have %i lives remaining"), Lives);

        return;
    }

    //Checks if the word is Isogram
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    //Prompt to Guess Again

    //Remove Life
    PrintLine(TEXT("Lost a life!"));
    --Lives;
    if (Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was : %s"), *HiddenWord);
        EndGame();
        return;
    }

    //Show the player Bulls and Cows
    //int32 Bulls, Cows;
    FBullCowCount Score = GetBullCows(Guess);
    PrintLine(TEXT("You have %i Bulls and %i Cows"), Score.Bulls, Score.Cows);
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);

}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            // if (Index < Comparison)
            // {
                if (Word[Index] == Word[Comparison])
                {
                    return false;
                }
            // }
        }
    }
    return true;
}


TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> TempValidWords;
 
    for(FString TempWord : WordList)
    {
        if( (TempWord.Len() >= 4 && TempWord.Len() <= 8) && IsIsogram(TempWord) )
        {
                TempValidWords.Emplace(TempWord);
        }
    }
    return TempValidWords;
}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const
{
    
    FBullCowCount Count= {0,0};

    //for ever index Guess is same as index Hidden, BullCount++
    //if not a bull was it a cow? If yes, CowCount++

    for(int32 GuessIndex = 0; GuessIndex < Guess.Len(); GuessIndex++)
    {
        if(Guess[GuessIndex] == HiddenWord[GuessIndex])
        {
            Count.Bulls++;
            continue;
        }

        for(int32 HiddenIndex = 0; HiddenIndex < HiddenWord.Len(); HiddenIndex++)
        {
            if(Guess[GuessIndex] == HiddenWord[HiddenIndex])
            {
                Count.Cows;
                break;
            }
        }
    }
    return Count;
}