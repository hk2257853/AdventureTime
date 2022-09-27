// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ASword::ASword()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SwordScene = CreateDefaultSubobject<USceneComponent>(TEXT("Sword Scene"));
	RootComponent = SwordScene;
	SwordMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sword Mesh"));
	SwordMesh->SetupAttachment(RootComponent);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collsion Box"));
	CollisionBox->SetupAttachment(SwordMesh);

}

// Called when the game starts or when spawned
void ASword::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASword::OnOverlap);

	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

}

void ASword::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{

	AActor* MyOwner = GetOwner();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		if (Player->GetSliceAnimationPosition()>0 && Player->GetSliceAnimationPosition() < ReqSliceAnimPosition)//&& >0
		{
			UE_LOG(LogTemp, Error, TEXT("SwordAttacked!"));
			UGameplayStatics::ApplyDamage(OtherActor, damage, GetInstigatorController(), this, damageType);
		}
	}

}

// Called every frame
void ASword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}