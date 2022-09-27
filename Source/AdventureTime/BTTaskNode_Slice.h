// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskNode_Slice.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURETIME_API UBTTaskNode_Slice : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Slice();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
