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

}

void ANPCAIController::RunBHTree()
{
	//RunBehaviorTree(BhTreeToRun);
	Blackboard->SetValueAsBool("IsActive", true);

}

void ANPCAIController::StopBhTree()
{
	Blackboard->SetValueAsBool("IsActive", false);

	
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

void ANPCAIController::NPCDeath(int ID)
{
	GameManagerRef->NPCDeath(ID);
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

			BhTreeToRun = tree;
			AttDamage = npc->AttackDamage;
			AttRange = npc->AttackRange;

			BehaviorComp = Cast<UBehaviorTreeComponent>(BrainComponent);
			RunBehaviorTree(BhTreeToRun);
		
		
		}
	}
}

TArray<AActor*> ANPCAIController::GetAllTowers()
{
	return GameManagerRef->GetAllTowers();
}
