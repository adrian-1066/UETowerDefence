// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyScript.h"

#include "NPCAIController.h"

// Sets default values
ABaseEnemyScript::ABaseEnemyScript()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

float ABaseEnemyScript::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount;
	if(CurrentHealth <= 0)
	{
		OnDeath();
	}
	return 0.0f;
	//return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ABaseEnemyScript::OnDeath()
{
	UE_LOG(LogTemp,Error,TEXT("NPC %d has dies"), NPCID);
	StopAttacking();
	SetActorLocation(FVector(-1000.0f+ (100.0f * NPCID), -1000.0f, -1000.0f + (100.0f * NPCID)));
	ANPCAIController* Con = Cast<ANPCAIController>(GetController());
	Con->NPCDeath(NPCID);
	
}

// Called when the game starts or when spawned
void ABaseEnemyScript::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	
}

// Called every frame
void ABaseEnemyScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseEnemyScript::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UBehaviorTree* ABaseEnemyScript::GetBhTree() const
{
	return BhTree;
}

void ABaseEnemyScript::StartAttacking(FVector SpawnLoc)
{
	CurrentHealth = MaxHealth;
	ANPCAIController* Con = Cast<ANPCAIController>(GetController());
	SetActorLocation(SpawnLoc);
	Con->RunBHTree();
}

void ABaseEnemyScript::StopAttacking()
{
	ANPCAIController* Con = Cast<ANPCAIController>(GetController());
	Con->StopBhTree();
}

