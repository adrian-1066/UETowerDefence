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
	
}

// Called every frame
void ATowerBaseScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMesh* ATowerBaseScript::GetTowerStaticMesh()
{
	return TowerMesh->GetStaticMesh();
}

