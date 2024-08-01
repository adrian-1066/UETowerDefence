// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TargetPrio.h"

#include "NavigationSystem.h"
#include "NPCAIController.h"

UBTTask_TargetPrio::UBTTask_TargetPrio(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Establish Prio";
}

EBTNodeResult::Type UBTTask_TargetPrio::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* conTemp = OwnerComp.GetAIOwner();
	ANPCAIController* AICON = Cast<ANPCAIController>(conTemp);
	if(AICON == nullptr)
	{
		UE_LOG(LogTemp,Warning,TEXT("failed to get ai con"));
	}

	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

bool UBTTask_TargetPrio::CanMoveToTarget(ANPCAIController* AICon, const FVector TargetLoc) const
{
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

	return Result.IsSuccessful();
}
