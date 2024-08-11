// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TargetPrio.h"

#include "NavigationSystem.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
UBTTask_TargetPrio::UBTTask_TargetPrio(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Establish Prio";
}
EBTNodeResult::Type UBTTask_TargetPrio::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> Towers;
	ANPCAIController* AICON = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	if (!AICON)
	{
		return EBTNodeResult::Failed;
	}

	// First, check the primary target
	if (CanMoveToTarget(AICON, AICON->TowerToAttack->GetActorLocation()))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), AICON->TowerToAttack->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("TargetObj", AICON->TowerToAttack);
		return EBTNodeResult::Succeeded;
	}
	Towers = AICON->GetAllTowers();
	// Then, check all other towers
	AActor* ClosetTower = nullptr;
	for (AActor* Tower : Towers)
	{
		if (CanMoveToTarget(AICON, Tower->GetActorLocation()))
		{
			if(ClosetTower == nullptr)
			{
				ClosetTower = Tower;
			}
			else
			{
				float CurrentDistance = FVector::Dist(ClosetTower->GetActorLocation(), AICON->GetPawn()->GetActorLocation());
				float NewDistance = FVector::Dist(Tower->GetActorLocation(), AICON->GetPawn()->GetActorLocation());
				if(NewDistance <= CurrentDistance)
				{
					ClosetTower = Tower;
				}
			}
			
		}
	}

	if(ClosetTower != nullptr)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLoc", ClosetTower->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("TargetObj", ClosetTower);
		return EBTNodeResult::Succeeded;
	}


	return EBTNodeResult::Failed;
}

bool UBTTask_TargetPrio::CanMoveToTarget(ANPCAIController* AICon, const FVector TargetLoc) const
{
	if(AICon == nullptr)
	{
		return false;
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AICon->GetWorld());

	if(NavSys == nullptr)
	{
		return false;
	}
	
	const float AcceptanceRadius = 500.0f;

	FPathFindingQuery Query;
	Query.StartLocation = AICon->GetPawn()->GetActorLocation();
	Query.EndLocation = TargetLoc;
	Query.NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
	Query.SetAllowPartialPaths(true); 

	FPathFindingResult Result = NavSys->FindPathSync(Query);

	if(Result.IsSuccessful() && Result.Path.IsValid() && Result.Path->IsValid())
	{
		FVector LastPathPoint = Result.Path->GetPathPoints().Last().Location;
		if(FVector::Dist(LastPathPoint, TargetLoc) <= AcceptanceRadius)
		{
			return true;
		}
	}

	return false;
	

}
