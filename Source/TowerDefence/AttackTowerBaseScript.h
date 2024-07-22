// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBaseScript.h"
#include "Components/SphereComponent.h"
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
private:
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent* SphereComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
	
};
