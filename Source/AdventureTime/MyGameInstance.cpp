// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

const FString UMyGameInstance::UNIQUE_SAVE_SLOT = "SaveData_0";


bool UMyGameInstance::IsNewGame()
{
	if (UGameplayStatics::DoesSaveGameExist(UNIQUE_SAVE_SLOT, 0))
	{
		return false;
	}
	return true;
}

bool UMyGameInstance::LoadGame()
{
	CurrentSaveGame = nullptr;

	USaveGame* Slot = UGameplayStatics::LoadGameFromSlot(UNIQUE_SAVE_SLOT, 0);

	if (Slot != nullptr)
	{
		CurrentSaveGame = Cast<UMainSaveGame>(Slot);

		if (CurrentSaveGame != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("[UMyGameInstance::LoadGame] Success loading %s"), *UNIQUE_SAVE_SLOT);

			return true;
		}
	}

	return false;
}

bool UMyGameInstance::CreateNewSaveGame()
{
	if (CurrentSaveGame == nullptr)
	{
		USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UMainSaveGame::StaticClass());

		if (NewSaveGame != nullptr)
		{
			CurrentSaveGame = Cast<UMainSaveGame>(NewSaveGame);
		}
	}
	else
	{
		CurrentSaveGame->CreateSlot(UNIQUE_SAVE_SLOT);
	}



	return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, UNIQUE_SAVE_SLOT, 0);

}

bool UMyGameInstance::SaveGame()
{

	if (CurrentSaveGame != nullptr)
	{
		return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, UNIQUE_SAVE_SLOT, 0);
	}

	return false;

}