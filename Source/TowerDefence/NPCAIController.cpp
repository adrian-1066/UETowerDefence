// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BaseEnemyScript.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	//BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ANPCAIController::RunBHTree()
{
	RunBehaviorTree(BhTreeToRun);
	
	UE_LOG(LogTemp,Warning,TEXT("the bh tree is now running"));
}

void ANPCAIController::StopBhTree()
{
	if (BehaviorComp)
	{
		BehaviorComp->StopLogic(TEXT("AI Stopped for round break"));
		UE_LOG(LogTemp, Warning, TEXT("Behavior tree stopped"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("BehaviorComp is null in StopBhTree"));
	}
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
			//BehaviorComp
			BhTreeToRun = tree;
				//RunBehaviorTree(tree);
			BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);
			UE_LOG(LogTemp,Warning,TEXT("the bh tree is now stored"));
			if(BehaviorComp)
			{
				UE_LOG(LogTemp,Warning,TEXT("have got BHComp"));	
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("BehaviorComp is null"));
			}
		}
	}
}
