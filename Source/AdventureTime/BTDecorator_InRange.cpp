// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_InRange.h"
#include "AIController.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_InRange::UBTDecorator_InRange()
{
	NodeName = (TEXT("InRange?"));
}

bool UBTDecorator_InRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (FVector::Dist(Player->GetActorLocation(), OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey())) < Range)
	{
		UE_LOG(LogTemp, Warning, TEXT("in range"));
		return true;
	}

	UE_LOG(LogTemp, Warning, TEXT("not in range"));

	return false;
}