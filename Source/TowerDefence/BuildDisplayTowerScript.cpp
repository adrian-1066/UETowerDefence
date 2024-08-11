// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildDisplayTowerScript.h"

#include "Math/UnitConversion.h"


ABuildDisplayTowerScript::ABuildDisplayTowerScript()
{
	TimeBetweenSwaps = 2.0f;
	TowerMesh->SetCollisionProfileName(TEXT("DisplayTower"));
	TowerMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly); 
	TowerMesh->SetGenerateOverlapEvents(true);
	
}

void ABuildDisplayTowerScript::BeginPlay()
{
	Super::BeginPlay();
	TowerMesh->OnComponentBeginOverlap.AddDynamic(this, &ABuildDisplayTowerScript::OnOverlapBegin);
	TowerMesh->OnComponentEndOverlap.AddDynamic(this, &ABuildDisplayTowerScript::OnOverlapEnd);

	TowerMesh->SetMaterial(0,CanPlaceMat);
}

void ABuildDisplayTowerScript::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CanBePlaced = false;
	TowerMesh->SetMaterial(0,CanNotPlaceMat);

}

void ABuildDisplayTowerScript::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	TowerMesh->SetMaterial(0,CanPlaceMat);
	CanBePlaced = true;
}

void ABuildDisplayTowerScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ABuildDisplayTowerScript::SwapMesh()
{
	if(TowerMesh->GetStaticMesh() == Mesh1)
	{
		TowerMesh->SetStaticMesh(Mesh2);
		TowerMesh->SetMaterial(0,CanPlaceMat);
	}
	else if(TowerMesh->GetStaticMesh() == Mesh2)
	{
		TowerMesh->SetStaticMesh(Mesh1);
		TowerMesh->SetMaterial(0,CanNotPlaceMat);
	}
}

void ABuildDisplayTowerScript::SetMesh(UStaticMesh* NewMesh)
{
	TowerMesh->SetStaticMesh(NewMesh);
}


