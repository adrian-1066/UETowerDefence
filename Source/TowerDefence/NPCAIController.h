// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
//#include "BehaviorTree/BehaviorTreeComponent.h"

#include "NPCAIController.generated.h"


/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ANPCAIController : public AAIController
{
	GENERATED_BODY()
public:
	explicit ANPCAIController(FObjectInitializer const& ObjectInitializer);
	UPROPERTY(Transient)
	UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY(Transient)
	UBlackboardComponent* BlackboardComponent;
	UPROPERTY()
	UBehaviorTree* BhTreeToRun;
	void RunBHTree();
	void StopBhTree();
protected:
	virtual void OnPossess(APawn* InPawn) override;
};
