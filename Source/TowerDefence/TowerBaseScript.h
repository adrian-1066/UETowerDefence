// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Image")
	UTexture2D* TowerDisplayTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float CurrentHealth;

	//void TakeDamage(float damage);

	virtual void TowerDeath();
	UPROPERTY(EditAnywhere)
	int testtwo;
	UFUNCTION(BlueprintCallable, Category="Components")
	UStaticMesh* GetTowerStaticMesh();
	UFUNCTION(BlueprintCallable, Category="Components")
	UTexture2D* GetTowerDisplayImage();

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
	int testone;

private:
	

	

	

};
