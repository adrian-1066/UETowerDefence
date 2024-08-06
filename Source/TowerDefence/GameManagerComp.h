// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TowerToDefendScript.h"
#include "BaseCharacterScript.h"
#include "BaseEnemyScript.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "GameFramework/Actor.h"
#include "NPCAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameManagerComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCE_API UGameManagerComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGameManagerComp();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	ATowerToDefendScript* DefencePointRef;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	TArray<AActor*> SpawnLocations;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	int TotalNumOfEnemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	int CurrentRound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	TSubclassOf<ABaseEnemyScript> EnemyToSpawn;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Info")
	//TSubclassOf<ANPCAIController> AICon;
	UPROPERTY()
	ABaseCharacterScript* PlayerCharacter;

	TArray<AActor*> GetAllTowers();
	void StartSetUp();
	void NextRoundStart();
	void EndRound();
	void LoseGame();
	void WinGame();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	void SpawnEnemies();
	void SetPlayerCharacter();
	int CurrentRoundSize;
	FTimerHandle TimerHandle;
	UPROPERTY()
	TArray<ABaseEnemyScript*> ListOfEnemies; 
		
};
