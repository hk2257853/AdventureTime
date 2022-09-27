// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "PlayerCharacter.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	CheckpointMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	CheckpointMesh->SetupAttachment(RootComponent);
	CheckpointBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion Box"));
	CheckpointBox->SetupAttachment(CheckpointMesh);

	bCanSave = false;
}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	CheckpointBox->OnComponentBeginOverlap.AddDynamic(this, &ACheckpoint::OnOverlap);
	CheckpointBox->OnComponentEndOverlap.AddDynamic(this, &ACheckpoint::OnOverlapEnd);
}

void ACheckpoint::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	CanSaveText = CreateWidget(GetWorld(), CanSaveTextClass);
	if (CanSaveText != nullptr)
	{
		bCanSave = true;
		CanSaveText->AddToViewport();
	}
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->SaveGame();

}

void ACheckpoint::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (CanSaveText != nullptr)
	{
		bCanSave = false;
		CanSaveText->RemoveFromViewport();
	}
}
