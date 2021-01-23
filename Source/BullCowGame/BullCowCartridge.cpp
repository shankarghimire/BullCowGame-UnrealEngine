// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    HiddenWord = TEXT("cake");
    PrintLine(TEXT("Welcome to BullCow Game!!!"));
    PrintLine(TEXT("Guess a 4 letter word !")); //Will be replaced by Magic Number
    PrintLine(TEXT("Press 'Enter' key to continue : "));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    //FString HiddenWord = TEXT("cake"); //Later will be relocated to next place to make it global
    //PrintLine(Input);
  
    if( HiddenWord == Input)
    {
        PrintLine(TEXT("You Win!"));
    }
    else
    {
        PrintLine(TEXT("Sorry! You Lose!"));
    }

}