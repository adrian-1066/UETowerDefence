// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBaseScript.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Materials/MaterialInterface.h"
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
	void SetMesh(UStaticMesh* NewMesh);

	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMesh* Mesh1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMesh* Mesh2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UMaterialInterface* CanPlaceMat;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UMaterialInterface* CanNotPlaceMat;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="State")
	bool CanBePlaced;
	float CurrentTime;
	float TimeBetweenSwaps;
private:
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
