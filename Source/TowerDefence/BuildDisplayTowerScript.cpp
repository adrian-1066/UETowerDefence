// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildDisplayTowerScript.h"

#include "Math/UnitConversion.h"


ABuildDisplayTowerScript::ABuildDisplayTowerScript()
{
	TimeBetweenSwaps = 2.0f;
}

void ABuildDisplayTowerScript::BeginPlay()
{
	Super::BeginPlay();
	TowerMesh->SetStaticMesh(Mesh1);
}

void ABuildDisplayTowerScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentTime += DeltaTime;
	if(CurrentTime >= TimeBetweenSwaps)
	{
		CurrentTime = 0.0f;
		SwapMesh();
	}
}

void ABuildDisplayTowerScript::SwapMesh()
{
	if(TowerMesh->GetStaticMesh() == Mesh1)
	{
		TowerMesh->SetStaticMesh(Mesh2);
	}
	else if(TowerMesh->GetStaticMesh() == Mesh2)
	{
		TowerMesh->SetStaticMesh(Mesh1);
	}
}


