// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerBaseScript.h"

// Sets default values
ATowerBaseScript::ATowerBaseScript()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TowerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TowerMesh"));
	
	RootComponent = TowerMesh;
	

}

// Called when the game starts or when spawned
void ATowerBaseScript::BeginPlay()
{
	Super::BeginPlay();
	//TowerMesh->OnComponentBeginOverlap.AddDynamic(this,&ATowerBaseScript::OnOverlapBegin);
	//TowerMesh->SetStaticMesh(StaticTowerMesh);
	
}

/*void ATowerBaseScript::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp,Warning,TEXT("collision detected"));
}*/

// Called every frame
void ATowerBaseScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ATowerBaseScript::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{

	UE_LOG(LogTemp,Warning,TEXT("tower has taken damage"));
	return 0.0f;
	//return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

/*void ATowerBaseScript::TakeDamage(float damage)
{
	CurrentHealth -= damage;
	if(CurrentHealth <= 0)
	{
		TowerDeath();
	}
}*/

void ATowerBaseScript::TowerDeath()
{
	UE_LOG(LogTemp,Warning,TEXT("Tower has died"));
}

UStaticMesh* ATowerBaseScript::GetTowerStaticMesh()
{
	return  TowerMesh ? TowerMesh->GetStaticMesh() : nullptr;
}

UTexture2D* ATowerBaseScript::GetTowerDisplayImage()
{
	return TowerDisplayTexture;
}

