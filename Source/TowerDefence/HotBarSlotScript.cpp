// Fill out your copyright notice in the Description page of Project Settings.


#include "HotBarSlotScript.h"


void UHotBarSlotScript::NativeConstruct()
{
	Super::NativeConstruct();
	MeshToDisplay = GetTowerStaticMesh();
	StartImageSetUp(GetDisplayImage());
	
}

UStaticMesh* UHotBarSlotScript::GetTowerStaticMesh() const
{
	ATowerBaseScript* DefTower = GetDefaultTowerObject();
	return DefTower && DefTower->TowerMesh ? DefTower->TowerMesh->GetStaticMesh() : nullptr;
}

UTexture2D* UHotBarSlotScript::GetDisplayImage() const
{
	ATowerBaseScript* DefTower = GetDefaultTowerObject();
	return DefTower->GetTowerDisplayImage();
}

ATowerBaseScript* UHotBarSlotScript::GetDefaultTowerObject() const
{
	if(TowerToSpawn)
	{
		return TowerToSpawn.GetDefaultObject();
	}
	return nullptr;
}
