// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerToDefendScript.h"
#include "GameManagerComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCE_API UGameManagerComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameManagerComp();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY()
	ATowerToDefendScript* DefencePointRef;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void GetTowerToDefend();
		
};
