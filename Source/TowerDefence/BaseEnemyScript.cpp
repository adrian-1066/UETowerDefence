
#include "BaseEnemyScript.h"
#include "NPCAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemyScript::ABaseEnemyScript()
{
 
	PrimaryActorTick.bCanEverTick = true;

}

float ABaseEnemyScript::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	if(!IsAlive)
	{
		return 0.0f;
	}
	CurrentHealth -= DamageAmount;
	if(CurrentHealth <= 0)
	{
		OnDeath();
	}
	return 0.0f;
}

void ABaseEnemyScript::TakeSlowDamage(float DamageAmount, float Reduction)
{
	if(!IsAlive)
	{
		return;
	}
	CurrentHealth -= DamageAmount;
	if(CurrentHealth <= 0)
	{
		OnDeath();
	}
	float TempSpeed = BaseMoveSpeed * Reduction;
	GetCharacterMovement()->MaxWalkSpeed = TempSpeed;
	GetWorld()->GetTimerManager().SetTimer(SlowTimer,this,&ABaseEnemyScript::RestoreSpeed, 5.0f,false);
}

void ABaseEnemyScript::StartFireDamage(float DamageAmount)
{
	FireTicks = 0;
	GetWorld()->GetTimerManager().ClearTimer(FireTimer);
	FireEffect(DamageAmount);
}

void ABaseEnemyScript::FireEffect(float DamageAmount)
{
	FireTicks++;
	if(!IsAlive)
	{
		return;
	}
	CurrentHealth -= DamageAmount;
	if(CurrentHealth <= 0)
	{
		OnDeath();
		return;
	}
	if(FireTicks >= 6)
	{
		return;
	}
	FTimerDelegate TimerDel;
	TimerDel.BindLambda([=](){FireEffect(DamageAmount);});
	GetWorld()->GetTimerManager().SetTimer(FireTimer,TimerDel, 0.25,false);
}

void ABaseEnemyScript::RestoreSpeed()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;
}

void ABaseEnemyScript::OnDeath()
{
	IsAlive = false;
	StopAttacking();
	SetActorLocation(FVector(-1000.0f+ (-1000.0f * NPCID), -1000.0f, -1000.0f + (-1000.0f * NPCID)));
	ANPCAIController* Con = Cast<ANPCAIController>(GetController());
	Con->NPCDeath(NPCID);
	
}

void ABaseEnemyScript::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;
	
}

void ABaseEnemyScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

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
	IsAlive = true;
	ANPCAIController* Con = Cast<ANPCAIController>(GetController());
	SetActorLocation(SpawnLoc);
	Con->RunBHTree();
}

void ABaseEnemyScript::StopAttacking()
{
	ANPCAIController* Con = Cast<ANPCAIController>(GetController());
	Con->StopBhTree();
}

