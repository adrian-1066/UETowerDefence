// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "TowerToDefendScript.h"
//#include "BehaviorTree/BehaviorTreeComponent.h"

#include "NPCAIController.generated.h"


class UGameManagerComp;
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
	UPROPERTY()
	ATowerToDefendScript* TowerToAttack;
	void SetGameManager(UGameManagerComp* ManagerRef);
protected:
	virtual void OnPossess(APawn* InPawn) override;
	
	
private:
	TArray<AActor*> GetAllTowers();
	UPROPERTY()
	UGameManagerComp* GameManagerRef;
};
