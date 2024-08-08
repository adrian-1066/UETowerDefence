// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTowerBaseScript.h"

#include "Engine/DamageEvents.h"

AAttackTowerBaseScript::AAttackTowerBaseScript()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("TowerPreset"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // No collision, only overlap
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetupAttachment(RootComponent);
	//RootComponent = SphereComponent;
}
void AAttackTowerBaseScript::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->SetSphereRadius(AttackRange);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAttackTowerBaseScript::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAttackTowerBaseScript::OnOverlapEnd);
	SpawnLocation = GetActorLocation();
}

void AAttackTowerBaseScript::OnDeath()
{
	SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z-1000.0f));
	//Super::OnDeath();
}

void AAttackTowerBaseScript::Respawn()
{
	CurrentHealth = MaxHealth;
	SetActorLocation(SpawnLocation);
}

void AAttackTowerBaseScript::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ListOfTargets.IsEmpty())
	{
		ListOfTargets.Add(OtherActor);
		AttackLoop();
		//GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&AAttackTowerBaseScript::AttackLoop,0.0f,true);
		//start attack
	}
	else
	{
		ListOfTargets.Add(OtherActor);	
	}
	
	//UE_LOG(LogTemp,Warning,TEXT("in attack Range"));
}

void AAttackTowerBaseScript::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ListOfTargets.Remove(OtherActor);
	if(ListOfTargets.IsEmpty())
	{
		//stop the attack loop
	}
	//UE_LOG(LogTemp,Warning,TEXT("no longer in attack Range"));
}

void AAttackTowerBaseScript::Attack(AActor* Target)
{
	FDamageEvent DamageEvent;
	Target->TakeDamage(AttackDamage, DamageEvent, GetWorld()->GetFirstPlayerController(),this);
	//CanAttack = false;
	//GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&AAttackTowerBaseScript::AttackReset,AttackSpeed,true);
}

void AAttackTowerBaseScript::AttackReset()
{
	CanAttack = true;
}

void AAttackTowerBaseScript::AttackLoop()
{
	//UE_LOG(LogTemp,Warning,TEXT("the number of targets is %d"), ListOfTargets.Num());
	for(int i = 0; i < TargetsPerAttack; i++)
	{
		if(i < ListOfTargets.Num())
		{
			Attack(ListOfTargets[i]);
		}
		else
		{
			break;
		}
	}

	if(!ListOfTargets.IsEmpty())
	{
		GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&AAttackTowerBaseScript::AttackLoop,AttackSpeed,false);
	}
	else
	{
		//UE_LOG(LogTemp,Warning,TEXT("attack has stopped due to no targets"));
	}
}


