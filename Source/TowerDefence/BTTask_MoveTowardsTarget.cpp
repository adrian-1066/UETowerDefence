// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveTowardsTarget.h"
#include "NavigationSystem.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MoveTowardsTarget::UBTTask_MoveTowardsTarget(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Move To Location";
}

EBTNodeResult::Type UBTTask_MoveTowardsTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(ANPCAIController* const control = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		if(auto* const npc = control->GetPawn())
		{
			if(auto* const NavSys = UNavigationSystemV1::GetCurrent(GetWorld()))
			{
				FNavLocation Loc;
				FVector AILoc = npc->GetActorLocation();
				FVector PlayerLoc = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
				Loc.Location = PlayerLoc;
				OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), Loc.Location);
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
				return EBTNodeResult::Succeeded;
				//OwnerComp.GetBlackboardComponent()
			}
		}
	}
	return EBTNodeResult::Failed;
}
