// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNPC.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"

// Sets default values
AQuestNPC::AQuestNPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PrimaryActorTick.bCanEverTick = false;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = Scene;
	QuestNPCMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	QuestNPCMesh->SetupAttachment(RootComponent);
	QuestNPCBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion Box"));
	QuestNPCBox->SetupAttachment(QuestNPCMesh);

}

// Called when the game starts or when spawned
void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();
	QuestNPCBox->OnComponentBeginOverlap.AddDynamic(this, &AQuestNPC::OnOverlap);
	QuestNPCBox->OnComponentEndOverlap.AddDynamic(this, &AQuestNPC::OnOverlapEnd);

}


void AQuestNPC::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->InterectNPC();
}

void AQuestNPC::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	Player->HideUi();
}

