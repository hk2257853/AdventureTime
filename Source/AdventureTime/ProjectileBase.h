// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class ADVENTURETIME_API AProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* projectileMovement;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* projectileMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UParticleSystemComponent* trailComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float damage = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile", meta = (AllowPrivateAccess = "true"))
		float projectileSpeed = 2000.f;

	UPROPERTY(EditAnywhere, Category = "Effects")
		UParticleSystem* hitParticle;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* hitSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
		USoundBase* launchSound;
	UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<UMatineeCameraShake> hitShake;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);



};
