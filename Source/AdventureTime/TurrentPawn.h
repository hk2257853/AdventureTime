// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurrentPawn.generated.h"

class UCapsuleComponent;
class AProjectileBase;
class UHealthComponent;

UCLASS()
class ADVENTURETIME_API ATurrentPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATurrentPawn();
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UCapsuleComponent* capsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* baseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* turretMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* projectileSpawn;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UHealthComponent* healthComponent;

	class APlayerCharacter* Player;

	//Variables for projectile
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> projectileClass;

	FTimerHandle fireRateTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Rate", meta = (AllowPrivateAccess = "true"))
		float fireRate = 2.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire Rate", meta = (AllowPrivateAccess = "true"))
		float fireRange = 500.f;

	void RotateTurret(FVector target);
	void Fire();
	void CheckFireCondition();
	float DistanceToPlayer();

};
