// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "GunEnemy.generated.h"

class AGun;

/**
 * 
 */
UCLASS()
class ADVENTURETIME_API AGunEnemy : public AEnemyCharacter
{
	GENERATED_BODY()
	
public: 
	void Shoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
		TSubclassOf<AGun> GunClass;

	UPROPERTY()
		AGun* Gun;

};
