// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "GameManagerComp.h"
#include "BaseEnemyScript.h"

ANPCAIController::ANPCAIController(FObjectInitializer const& ObjectInitializer)
{
	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	//BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void ANPCAIController::RunBHTree()
{
	//RunBehaviorTree(BhTreeToRun);
	Blackboard->SetValueAsBool("IsActive", true);
	UE_LOG(LogTemp,Warning,TEXT("the bh tree is now running"));
}

void ANPCAIController::StopBhTree()
{
	Blackboard->SetValueAsBool("IsActive", false);
	UE_LOG(LogTemp, Warning, TEXT("Behavior tree stopped"));
	
}

void ANPCAIController::SetGameManager(UGameManagerComp* ManagerRef)
{
	GameManagerRef = ManagerRef;
}


void ANPCAIController::HasJustAttacked()
{
	CanAttack = false;
	GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ANPCAIController::AttackReset,2.0f,true);
}
void ANPCAIController::AttackReset()
{
	CanAttack = true;
}


void ANPCAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(ABaseEnemyScript* const npc =  Cast<ABaseEnemyScript>(InPawn))
	{
		if(UBehaviorTree* const tree = npc->GetBhTree())
		{
			UBlackboardComponent* b;
			
			
			CanAttack = true;
			UseBlackboard(tree->BlackboardAsset, b);
			Blackboard = b;
			//BehaviorComp
			BhTreeToRun = tree;
			AttDamage = npc->AttackDamage;
			AttRange = npc->AttackRange;
				//RunBehaviorTree(tree);
			BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);
			RunBehaviorTree(BhTreeToRun);
			UE_LOG(LogTemp,Warning,TEXT("the bh tree is now stored"));
			if(BehaviorComp)
			{
				//UE_LOG(LogTemp,Warning,TEXT("have got BHComp"));	
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("BehaviorComp is null"));
			}
		}
	}
}

TArray<AActor*> ANPCAIController::GetAllTowers()
{
	return GameManagerRef->GetAllTowers();
}
