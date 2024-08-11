// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TargetPrio.h"

#include "NavigationSystem.h"
#include "NPCAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
UBTTask_TargetPrio::UBTTask_TargetPrio(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Establish Prio";
}
/*
EBTNodeResult::Type UBTTask_TargetPrio::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* conTemp = OwnerComp.GetAIOwner();
	ANPCAIController* AICON = Cast<ANPCAIController>(conTemp);
	if(AICON == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("failed to get ai con"));
	}

	if(CanMoveToTarget(AICON, AICON->TowerToAttack->GetActorLocation()))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),AICON->TowerToAttack->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("TargetObj", AICON->TowerToAttack);
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}

	UE_LOG(LogTemp,Warning,TEXT("num of towers is: %d"), AICON->GetAllTowers().Num());
	for(int i = 0; i < AICON->GetAllTowers().Num(); i++)
	{
		if(CanMoveToTarget(AICON, AICON->GetAllTowers()[i]->GetActorLocation()))
		{
			UE_LOG(LogTemp,Warning,TEXT("can move to tower"));
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(),AICON->GetAllTowers()[i]->GetActorLocation());
			OwnerComp.GetBlackboardComponent()->SetValueAsObject("TargetObj",AICON->GetAllTowers()[i]);
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			return EBTNodeResult::Succeeded;
		}
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	return EBTNodeResult::Failed;

	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}*/
EBTNodeResult::Type UBTTask_TargetPrio::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TArray<AActor*> Towers;
	ANPCAIController* AICON = Cast<ANPCAIController>(OwnerComp.GetAIOwner());
	if (!AICON)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to get AI controller"));
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
	UE_LOG(LogTemp,Warning,TEXT("there are %d towers"), Towers.Num());
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
		UE_LOG(LogTemp, Warning, TEXT("Found a reachable tower"));
		OwnerComp.GetBlackboardComponent()->SetValueAsVector("TargetLoc", ClosetTower->GetActorLocation());
		OwnerComp.GetBlackboardComponent()->SetValueAsObject("TargetObj", ClosetTower);
		return EBTNodeResult::Succeeded;
	}

	// If no target can be found
	UE_LOG(LogTemp, Warning, TEXT("No reachable towers found"));
	return EBTNodeResult::Failed;
}

bool UBTTask_TargetPrio::CanMoveToTarget(ANPCAIController* AICon, const FVector TargetLoc) const
{
	if(AICon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI Controller"));
		return false;
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AICon->GetWorld());

	if(NavSys == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Navigation System"));
		return false;
	}

	// Define the acceptance radius
	const float AcceptanceRadius = 500.0f;

	FPathFindingQuery Query;
	Query.StartLocation = AICon->GetPawn()->GetActorLocation();
	Query.EndLocation = TargetLoc;
	Query.NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
	//Query.QueryFilter = UNavigationQueryFilter::GetQueryFilter<UNavigationQueryFilter>(NavSys);
	Query.SetAllowPartialPaths(true); // Allow partial paths to check for near-by locations

	FPathFindingResult Result = NavSys->FindPathSync(Query);

	// Check if the pathfinding operation was successful and if a path was found
	if(Result.IsSuccessful() && Result.Path.IsValid() && Result.Path->IsValid())
	{
		// Get the last point in the path
		FVector LastPathPoint = Result.Path->GetPathPoints().Last().Location;

		// Check if the last point is within the acceptance radius
		if(FVector::Dist(LastPathPoint, TargetLoc) <= AcceptanceRadius)
		{
			return true;
		}
	}

	return false;
	/*
	if(AICon == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI Controller"));
		return false;
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AICon->GetWorld());

	if(NavSys == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Navigation System"));
		return false;
	}

	FPathFindingQuery Query;
	Query.StartLocation = AICon->GetPawn()->GetActorLocation();
	Query.EndLocation = TargetLoc;
	Query.NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
	FPathFindingResult Result = NavSys->FindPathSync(Query);

	// Check if the pathfinding operation was successful and if a path was found
	if(Result.IsSuccessful() && Result.Path.IsValid() && Result.Path->IsValid())
	{
		return true;
	}
*/
	return false;
	/*
	
	if(AICon == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("No ai con"));
		return false;
	}

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(AICon->GetWorld());

	if(NavSys == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("No Nav Sys"));
		return false;
	}

	FPathFindingQuery Query;
	Query.StartLocation = AICon->GetPawn()->GetActorLocation();
	Query.EndLocation = TargetLoc;
	Query.NavData = NavSys->GetDefaultNavDataInstance(FNavigationSystem::DontCreate);
	FPathFindingResult Result = NavSys->FindPathSync(Query);

	return Result.IsSuccessful();*/
}
