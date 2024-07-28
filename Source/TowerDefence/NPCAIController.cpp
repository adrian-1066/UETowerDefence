// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"

#include "BaseEnemyScript.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
}

void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(ABaseEnemyScript* const npc =  Cast<ABaseEnemyScript>(InPawn))
	{
		if(UBehaviorTree* const tree = npc->GetBhTree())
		{
			UBlackboardComponent* b;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			RunBehaviorTree(tree);
		}
	}
}
