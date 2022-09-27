// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Sword.generated.h"

//class ASword_TriggerBox;
UCLASS()
class ADVENTURETIME_API ASword : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASword();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		USceneComponent* SwordScene = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		UStaticMeshComponent* SwordMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		UBoxComponent* CollisionBox = nullptr;



	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<UDamageType> damageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (AllowPrivateAccess = "true"))
		float damage = 50.f;

	UPROPERTY(EditAnywhere)
		float ReqSliceAnimPosition = 0.83f;

	UPROPERTY()
		class APlayerCharacter* Player;
};
