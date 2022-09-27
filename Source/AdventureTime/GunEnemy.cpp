// Fill out your copyright notice in the Description page of Project Settings.


#include "GunEnemy.h"
#include "Gun.h"

// Called when the game starts or when spawned
void AGunEnemy::BeginPlay()
{
	Super::BeginPlay();
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SwordSocket"));
	Gun->SetOwner(this);

}

void AGunEnemy::Shoot()
{
	Gun->Fire();
}