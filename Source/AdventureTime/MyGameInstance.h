// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameFramework/SaveGame.h"
#include "MyGameInstance.generated.h"


//this class has all the data I want to store on game save.
UCLASS()
class ADVENTURETIME_API UMainSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString SaveGameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FDateTime CreationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SaveLocation; //location to be saved.


	void CreateSlot(const FString& SlotName)
	{
		SaveGameName = SlotName;
		CreationTime = FDateTime::Now();
		SaveLocation=FVector(0,0,0);
	};

};

/**
 * 
 */
UCLASS()
class ADVENTURETIME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	static const FString UNIQUE_SAVE_SLOT;

public:

	UPROPERTY()
		UMainSaveGame* CurrentSaveGame;

public:

	bool IsNewGame();

	bool CreateNewSaveGame();

	bool LoadGame();

	bool SaveGame();

	
};
