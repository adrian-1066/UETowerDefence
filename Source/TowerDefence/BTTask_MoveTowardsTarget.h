// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_MoveTowardsTarget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UBTTask_MoveTowardsTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_MoveTowardsTarget(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
