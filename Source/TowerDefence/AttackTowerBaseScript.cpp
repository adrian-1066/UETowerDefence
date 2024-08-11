// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTowerBaseScript.h"

#include "BaseCharacterScript.h"
#include "BaseEnemyScript.h"
#include "Engine/DamageEvents.h"

AAttackTowerBaseScript::AAttackTowerBaseScript()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(50.0f);
	SphereComponent->SetCollisionProfileName(TEXT("TowerPreset"));
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // No collision, only overlap

	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCanEverAffectNavigation(false);
	SphereComponent->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->InitBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxComponent->SetCollisionProfileName(TEXT("BlockAll"));
	BoxComponent->SetCanEverAffectNavigation(true);
	BoxComponent->SetupAttachment(RootComponent);
	UNavModifierComponent* NavModifier = CreateDefaultSubobject<UNavModifierComponent>(TEXT("NavModifier"));

	
}
void AAttackTowerBaseScript::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->SetSphereRadius(AttackRange);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAttackTowerBaseScript::OnOverlapBegin);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AAttackTowerBaseScript::OnOverlapEnd);
	SpawnLocation = GetActorLocation();
	AudioPlayer = FindComponentByClass<UAwakeAudioPlayer>();
	if(AudioPlayer)
	{
		UE_LOG(LogTemp,Warning,TEXT("found audio"));
	}
	DetectOverlappingActors();
}

void AAttackTowerBaseScript::OnDeath()
{
	//Destroy();
	SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y,GetActorLocation().Z-10000.0f));
	ABaseCharacterScript* Player = Cast<ABaseCharacterScript>( GetWorld()->GetFirstPlayerController()->GetCharacter());
	if(Player)
	{
		Player->TowersThatHaveBeenPlaced.RemoveSingle(this);
	}
	Destroy();
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
	}
	else
	{
		ListOfTargets.Add(OtherActor);	
	}
	
}

void AAttackTowerBaseScript::DetectOverlappingActors()
{
	TArray<AActor*> OverlappingActors;
	SphereComponent->GetOverlappingActors(OverlappingActors,ABaseEnemyScript::StaticClass());

	for (AActor* Actor : OverlappingActors)
	{
		if (Actor)
		{
			OnOverlapBegin(SphereComponent, Actor, nullptr, 0, false, FHitResult());
		}
	}
}


void AAttackTowerBaseScript::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ListOfTargets.Remove(OtherActor);
}

void AAttackTowerBaseScript::Attack(AActor* Target)
{
	UE_LOG(LogTemp,Warning,TEXT("attacking"));
	FDamageEvent DamageEvent;
	Target->TakeDamage(AttackDamage, DamageEvent, GetWorld()->GetFirstPlayerController(),this);

}

void AAttackTowerBaseScript::AttackReset()
{
	CanAttack = true;
}

void AAttackTowerBaseScript::AttackLoop()
{
	for(int i = 0; i < TargetsPerAttack; i++)
	{
		if(i < ListOfTargets.Num())
		{
			AudioPlayer->PlaySound("AttackSound");
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
	
}


