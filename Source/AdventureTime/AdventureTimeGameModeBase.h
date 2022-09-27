// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Definition.h"
#include "AdventureTimeGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURETIME_API AAdventureTimeGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest System")
		class UQuestData* QuestDatabase;

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Quest System")
		FQuest FindQuest(FName QuestID, bool& Success);

	FQuest FindQuest_Implementation(FName QuestID, bool& Success);


	
};
