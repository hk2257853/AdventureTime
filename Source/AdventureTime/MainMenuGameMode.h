// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURETIME_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Game Settings")
		class UMyGameInstance* GameInstance;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu Events")
		void OnShowMainMenu(bool NewGame);

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Menu Events")
		void OnNewGame(FName MapNameToLoad);

	void OnNewGame_Implementation(FName MapNameToLoad); //_Implementation is req

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Menu Events")
		void OnLoadGame(FName MapNameToLoad);

	void OnLoadGame_Implementation(FName MapNameToLoad);

};
