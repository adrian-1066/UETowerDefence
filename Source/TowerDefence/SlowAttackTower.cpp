// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowAttackTower.h"

#include "BaseEnemyScript.h"

void ASlowAttackTower::Attack(AActor* Target)
{
	ABaseEnemyScript* NPC = Cast<ABaseEnemyScript>(Target);
	if(NPC)
	{
		UE_LOG(LogTemp,Warning,TEXT("slow tower is targeting npc"));
		NPC->TakeSlowDamage(AttackDamage,SlowReduction);
	}
	//Super::Attack(Target);
}
