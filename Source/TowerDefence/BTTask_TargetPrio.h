// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "NPCAIController.h"
#include "BTTask_TargetPrio.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UBTTask_TargetPrio : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	explicit UBTTask_TargetPrio(FObjectInitializer const& ObjectInitializer);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
private:
	bool CanMoveToTarget(ANPCAIController* AICon, const FVector TargetLoc) const;
};
