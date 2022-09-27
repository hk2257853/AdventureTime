// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "GunEnemy.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{

	NodeName = (TEXT("Shoot"));

}

EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AGunEnemy* Enemy = Cast<AGunEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy) 
	{
		Enemy->Shoot();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}