// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackTowerBaseScript.h"
#include "DOTAttackTowerScript.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ADOTAttackTowerScript : public AAttackTowerBaseScript
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float DamagePerTick;
protected:
	void Attack(AActor* Target) override;
	
};
