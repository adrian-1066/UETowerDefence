// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "BaseEnemyScript.generated.h"

UCLASS()
class TOWERDEFENCE_API ABaseEnemyScript : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyScript();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UBehaviorTree* GetBhTree() const;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	bool IsAlive;
	void StartAttacking(FVector SpawnLoc);
	void StopAttacking();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float AttackRange;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float AttackDamage;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float MaxHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	float CurrentHealth;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	int NPCID;
	float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	void OnDeath();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(AllowPrivateAccess="true"))
	UBehaviorTree* BhTree;

};
