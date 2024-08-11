// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBaseScript.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "NavigationSystem.h"
#include "NavModifierComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "AwakeAudioPlayer.h"
#include "AttackTowerBaseScript.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API AAttackTowerBaseScript : public ATowerBaseScript
{
	GENERATED_BODY()
public:
	AAttackTowerBaseScript();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float AttackRange;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float AttackSpeed;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float AttackDamage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	int TargetsPerAttack;
	UAwakeAudioPlayer* AudioPlayer;
	void OnDeath() override;
	void Respawn();
private:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* SphereComponent;
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	UBoxComponent* BoxComponent;
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	FTimerHandle AttackTimer;

	void DetectOverlappingActors();
	void AttackReset();
	void AttackLoop();
	bool CanAttack;
	UPROPERTY()
	TArray<AActor*> ListOfTargets;
	FVector SpawnLocation;
protected:
	virtual void BeginPlay() override;
	virtual void Attack(AActor* Target);
};


