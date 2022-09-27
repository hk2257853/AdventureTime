// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

class AProjectileBase;

UCLASS()
class ADVENTURETIME_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		USceneComponent* GunScene = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		UStaticMeshComponent* GunMesh = nullptr;

	//Variables for proejectile
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile Type", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<AProjectileBase> projectileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		USceneComponent* projectileSpawn;

};
