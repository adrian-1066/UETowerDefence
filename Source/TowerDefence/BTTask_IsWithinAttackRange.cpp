// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_IsWithinAttackRange.h"
#include "GameFramework/Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Engine/DamageEvents.h"

UBTTask_IsWithinAttackRange::UBTTask_IsWithinAttackRange(FObjectInitializer const& ObjectInitializer)
{
	NodeName = "Is Within Attack Range";
}
/*
EBTNodeResult::Type UBTTask_IsWithinAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	
	if(AAIController* AiCon = OwnerComp.GetAIOwner())
	{
		if(ANPCAIController* NPCCon = Cast<ANPCAIController>(AiCon))
		{
			UBlackboardComponent* BlackboardComponent = NPCCon->GetBlackboardComponent();
			if(BlackboardComponent)
			{
				if(!NPCCon->CanAttack)
				{
					//UE_LOG(LogTemp,Warning,TEXT("ai can not attack yet"));
					FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
					return EBTNodeResult::Succeeded;
				}
				AActor* Target = Cast<AActor>(BlackboardComponent->GetValueAsObject("TargetObj"));
				if(Target)
				{
					AActor* NPC = NPCCon->GetPawn();
					if(NPC)
					{
						float DistanceToTarget = FVector::Dist(Target->GetActorLocation(),NPC->GetActorLocation());
						if(DistanceToTarget <= NPCCon->AttRange)
						{
							//do the attack
							FDamageEvent DamageEvent;
							
							Target->TakeDamage(NPCCon->AttDamage,DamageEvent,NPCCon,NPC);
							NPCCon->HasJustAttacked();
							FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
							return EBTNodeResult::Succeeded;
						}
						FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
						return EBTNodeResult::Succeeded;
					}
					else
					{
						UE_LOG(LogTemp,Warning,TEXT("could not get npc"));
					}
				}
				else
				{
					UE_LOG(LogTemp,Warning,TEXT("could not get target"));
				}
			}
			else
			{
				UE_LOG(LogTemp,Warning,TEXT("could not get blackboard component"));
			}
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("could not cast to npc con"));
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("could not get ai con"))
	}
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}*/
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
					// Attack the target
					FDamageEvent DamageEvent;
					Target->TakeDamage(NPCCon->AttDamage, DamageEvent, NPCCon, NPC);
					NPCCon->HasJustAttacked();

					// Task succeeds only after attack
					return EBTNodeResult::Succeeded;
				}
				else
				{
					// Not in range, consider failure or task continuation
					return EBTNodeResult::Failed;
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot attack yet or no valid blackboard component"));
		}
	}

	// Failure condition
	return EBTNodeResult::Failed;
}
