// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBaseScript.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "BuildDisplayTowerScript.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API ABuildDisplayTowerScript : public ATowerBaseScript
{
	GENERATED_BODY()

public:
	ABuildDisplayTowerScript();
	virtual void Tick(float DeltaTime) override;
	void SwapMesh();

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMesh* Mesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMesh* Mesh2;

	float CurrentTime;
	float TimeBetweenSwaps;
};
