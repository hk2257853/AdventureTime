// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Definition.generated.h"

UCLASS()
class ADVENTURETIME_API ADefinition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADefinition();

};

USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		FName CharacterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		FName QuestID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		FText Message;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		FText SortDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		FText CompleteMessage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		FName ItemID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Quest")
		UTexture2D* ItemQuestTexture;

};


UCLASS(BlueprintType)
class UQuestData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Quest")
		TArray<FQuest> QuestData;
};

USTRUCT(BlueprintType)
struct FQuestItem
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		FName QuestID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
		bool IsCompleted;
};
