// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IsWithinAttackRange.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"

UBTTask_IsWithinAttackRange::UBTTask_IsWithinAttackRange(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Is Within Attack Range";
}

EBTNodeResult::Type UBTTask_IsWithinAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (ANPCAIController* NPCCon = Cast<ANPCAIController>(OwnerComp.GetAIOwner()))
	{
		UBlackboardComponent* BlackboardComponent = NPCCon->GetBlackboardComponent();
		if (BlackboardComponent && NPCCon->CanAttack)
		{
			AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetObj"));
			AActor* NPC = NPCCon->GetPawn();

			if (Target && NPC)
			{
				float DistanceToTarget = FVector::Dist(Target->GetActorLocation(), NPC->GetActorLocation());
				if (DistanceToTarget <= NPCCon->AttRange)
				{
			
					FDamageEvent DamageEvent;
					Target->TakeDamage(NPCCon->AttDamage, DamageEvent, NPCCon, NPC);
					NPCCon->HasJustAttacked();

				
					return EBTNodeResult::Succeeded;
				}
				else
				{
					return EBTNodeResult::Failed;
				}
			}
		}
	}


	return EBTNodeResult::Failed;
}
