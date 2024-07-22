// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTowerBaseScript.h"

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
}

void AAttackTowerBaseScript::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("in attack Range"));
}

void AAttackTowerBaseScript::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp,Warning,TEXT("no longer in attack Range"));
}


