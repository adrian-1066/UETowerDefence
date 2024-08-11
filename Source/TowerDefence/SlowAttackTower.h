// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackTowerBaseScript.h"
#include "SlowAttackTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ASlowAttackTower : public AAttackTowerBaseScript
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float SlowReduction;
protected:
	void Attack(AActor* Target) override;
};
