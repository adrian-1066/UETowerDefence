// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Engine/Texture2D.h"
#include "TowerBaseScript.h"
#include "HotBarSlotScript.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENCE_API UHotBarSlotScript : public UUserWidget
{
	GENERATED_BODY()

public:
	

	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	UStaticMesh* MeshToDisplay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	TSubclassOf<ATowerBaseScript> TowerToSpawn;

	UFUNCTION(BlueprintCallable, Category = "TowerWidget")
	UStaticMesh* GetTowerStaticMesh() const;
	UFUNCTION(BlueprintCallable,Category="TowerWidget")
	UTexture2D* GetDisplayImage() const;
	UFUNCTION(BlueprintImplementableEvent, Category="Image")
	void StartImageSetUp(UTexture2D* ImageToDisplay);
	


private:
	ATowerBaseScript* GetDefaultTowerObject() const;
};
