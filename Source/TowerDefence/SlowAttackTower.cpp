// Fill out your copyright notice in the Description page of Project Settings.


#include "SlowAttackTower.h"

#include "BaseEnemyScript.h"

void ASlowAttackTower::Attack(AActor* Target)
{
	ABaseEnemyScript* NPC = Cast<ABaseEnemyScript>(Target);
	if(NPC)
	{

		NPC->TakeSlowDamage(AttackDamage,SlowReduction);
	}
	//Super::Attack(Target);
}
