// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBaseScript.h"


ATowerBaseScript::ATowerBaseScript()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	
	RootComponent = TowerMesh;
	

}


void ATowerBaseScript::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;

	
}


void ATowerBaseScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATowerBaseScript::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	
	CurrentHealth -= DamageAmount;
	if(CurrentHealth <= 0.0f)
	{
		OnDeath();
	}
	return 0.0f;

}

void ATowerBaseScript::OnDeath()
{
	
}



void ATowerBaseScript::TowerDeath()
{

}

UStaticMesh* ATowerBaseScript::GetTowerStaticMesh()
{
	return  TowerMesh ? TowerMesh->GetStaticMesh() : nullptr;
}

UTexture2D* ATowerBaseScript::GetTowerDisplayImage()
{
	return TowerDisplayTexture;
}

