// Fill out your copyright notice in the Description page of Project Settings.


#include "TurrentPawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerCharacter.h"
#include "ProjectileBase.h"
#include "HealthComponent.h"

// Sets default values
ATurrentPawn::ATurrentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = capsuleComponent;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	baseMesh->SetupAttachment(RootComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	projectileSpawn->SetupAttachment(turretMesh);

	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));


}

// Called when the game starts or when spawned
void ATurrentPawn::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorld()->GetTimerManager().SetTimer(fireRateTimer, this, &ATurrentPawn::CheckFireCondition, fireRate, true, false);

}

// Called every frame
void ATurrentPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!Player || DistanceToPlayer() > fireRange) { return; }
	RotateTurret(Player->GetActorLocation());

}


void ATurrentPawn::RotateTurret(FVector target)
{
	FVector turretLoc = turretMesh->GetComponentLocation();
	FRotator turretRot = UKismetMathLibrary::FindLookAtRotation(turretLoc, FVector(target.X, target.Y, turretMesh->GetComponentLocation().Z));

	turretMesh->SetWorldRotation(turretRot);

}

void ATurrentPawn::Fire()
{
	FVector projectileSpawnLoc = projectileSpawn->GetComponentLocation();
	FRotator projectileSpawnRot = projectileSpawn->GetComponentRotation();

	if (projectileClass) {
		AProjectileBase* tempProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectileClass, projectileSpawnLoc, projectileSpawnRot);
		tempProjectile->SetOwner(this);
	}

}

void ATurrentPawn::CheckFireCondition()
{
	//If Player is dead, then return
	if (!Player) { return; }

	if (DistanceToPlayer() <= fireRange /*&& Player->GetIsPlayerAlive()*/) {
		Fire();
	}

}

float ATurrentPawn::DistanceToPlayer()
{
	//If Player is dead, then return distance 0
	if (!Player) 	{ return 0.f;}

	float dist = (Player->GetActorLocation() - GetActorLocation()).Size();
	return dist;
}

