// Fill out your copyright notice in the Description page of Project Settings.


#include "DOTAttackTowerScript.h"

#include "BaseEnemyScript.h"

void ADOTAttackTowerScript::Attack(AActor* Target)
{
	ABaseEnemyScript* NPC = Cast<ABaseEnemyScript>(Target);
	if(NPC)
	{
	
		NPC->StartFireDamage(DamagePerTick);
	}
}
