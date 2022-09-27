// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "ProjectileBase.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunScene = CreateDefaultSubobject<USceneComponent>(TEXT("Gun Scene"));
	RootComponent = GunScene;
	GunMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Skeletal Mesh"));
	GunMesh->SetupAttachment(RootComponent);

	projectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	projectileSpawn->SetupAttachment(GunMesh);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::Fire()
{
	FVector projectileSpawnLoc = projectileSpawn->GetComponentLocation();
	FRotator projectileSpawnRot = projectileSpawn->GetComponentRotation();

	if (projectileClass) {
		AProjectileBase* tempProjectile = GetWorld()->SpawnActor<AProjectileBase>(projectileClass, projectileSpawnLoc, projectileSpawnRot);
		tempProjectile->SetOwner(this);
	}

}




