// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Slice.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "SwordEnemyChar.h"

UBTTaskNode_Slice::UBTTaskNode_Slice()
{

	NodeName = (TEXT("Slice"));

}

EBTNodeResult::Type UBTTaskNode_Slice::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ASwordEnemyChar* Enemy = Cast<ASwordEnemyChar>(OwnerComp.GetAIOwner()->GetPawn());
	if (Enemy)
	{
		Enemy->Cut();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
