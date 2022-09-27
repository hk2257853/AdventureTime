// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "SwordEnemyChar.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURETIME_API ASwordEnemyChar : public AEnemyCharacter
{
	GENERATED_BODY()
	
public: 
	UFUNCTION(BlueprintCallable, Category = "Overlap")
		void OnSwordOverlap(AActor* OtherActor);
	void Cut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


private:
	float GetEnemySliceAnimationPosition();



		UPROPERTY(EditAnywhere, Category = "Animation")
		UAnimMontage* Slice;

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float damage = 50.f;

	UPROPERTY(EditAnywhere)
		float ReqSliceAnimPosition = 0.83f;

};
