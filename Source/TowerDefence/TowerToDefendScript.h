// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
//#include "GameManagerComp.h"
#include "TowerBaseScript.h"
#include "TowerToDefendScript.generated.h"

//class UGameManagerComp;
/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ATowerToDefendScript : public ATowerBaseScript
{
	GENERATED_BODY()
public:
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void OnDeath() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Game")
	AActor* GameManager;
	
};
