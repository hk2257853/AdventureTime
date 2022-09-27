// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Checkpoint.generated.h"

UCLASS()
class ADVENTURETIME_API ACheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckpoint();
	bool bCanSave = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		USceneComponent* Scene = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		UStaticMeshComponent* CheckpointMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components", meta = (AllowPrivaeAccess = "true"))
		UBoxComponent* CheckpointBox = nullptr;

	UFUNCTION()
		void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> CanSaveTextClass;

	UUserWidget* CanSaveText;

};
