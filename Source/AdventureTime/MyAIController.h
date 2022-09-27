// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURETIME_API AMyAIController : public AAIController
{
	GENERATED_BODY()
private:
	UPROPERTY(EditAnywhere)
		class UBehaviorTree* AIBehavior;
	UPROPERTY(EditAnywhere)
		float AcceptanceRadius = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
