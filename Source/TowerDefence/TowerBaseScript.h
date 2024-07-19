// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "TowerBaseScript.generated.h"

UCLASS()
class TOWERDEFENCE_API ATowerBaseScript : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerBaseScript();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* TowerMesh;

	//UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Components")
	//UStaticMesh* StaticTowerMesh;
	UPROPERTY(EditAnywhere)
	int testtwo;
	UFUNCTION(BlueprintCallable, Category="Components")
	UStaticMesh* GetTowerStaticMesh();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	int testone;
	

	

	

};
