// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordEnemyChar.h"
#include "Kismet/GameplayStatics.h"

void ASwordEnemyChar::BeginPlay()
{
	Super::BeginPlay();
}

void ASwordEnemyChar::Cut()
{
	PlayAnimMontage(Slice);
}

float ASwordEnemyChar::GetEnemySliceAnimationPosition()
{
	if (GetMesh()->GetAnimInstance())
	{
		return GetMesh()->GetAnimInstance()->Montage_GetPosition(Slice);
	}
	return 0;
}
					//this is already there
void ASwordEnemyChar::OnSwordOverlap(AActor* OtherActor)
{
	//from there I need to work. A function that gets these 2 for me like in quest
	if (OtherActor && OtherActor != this)
	{
		if (GetEnemySliceAnimationPosition() > 0 && GetEnemySliceAnimationPosition() < ReqSliceAnimPosition) //&& >0
		{
			UE_LOG(LogTemp, Error, TEXT("Enemy SwordAttacked!"));
			UGameplayStatics::ApplyDamage(OtherActor, damage, GetInstigatorController(), this, damageType);
		}
	}
}
