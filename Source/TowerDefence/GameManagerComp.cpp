// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerComp.h"

// Sets default values for this component's properties
UGameManagerComp::UGameManagerComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
// Called when the game starts
void UGameManagerComp::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerCharacter();
	StartSetUp();
}

void UGameManagerComp::StartSetUp()
{
	SpawnEnemies();
	CurrentRound = 1;
}

void UGameManagerComp::NextRoundStart()
{
}

void UGameManagerComp::EndRound()
{
	CurrentRound++;
}

void UGameManagerComp::SpawnEnemies()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = GetOwner();
		SpawnParams.Instigator = GetOwner()->GetInstigator();
		for(int i = 0; i < TotalNumOfEnemies; i++ )
		{
			FVector SpawnLocation = FVector(100.0f * i + i, -1000.0f, 88.0f);
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AActor* SpawnedActor = World->SpawnActor<ABaseEnemyScript>(EnemyToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			if (SpawnedActor)
			{
				ABaseEnemyScript* SpawnedEnemy = Cast<ABaseEnemyScript>(SpawnedActor);
				if(SpawnedEnemy)
				{
					UE_LOG(LogTemp,Warning,TEXT("correct Enemy Has Spawned"));
					ANPCAIController* AIConToCon = GetWorld()->SpawnActor<ANPCAIController>(ANPCAIController::StaticClass());
					AIConToCon->Possess(SpawnedEnemy);
					ListOfEnemies.Add(SpawnedEnemy);
					if(i == 0)
					{
						SpawnedEnemy->StartAttacking();
						SpawnedEnemy->StopAttacking();
					}
				}
				else
				{
					UE_LOG(LogTemp,Warning,TEXT("spawn failed"));
				}
			}
		}
	}
}

void UGameManagerComp::SetPlayerCharacter()
{
	ACharacter* PC = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ABaseCharacterScript* ABCS = Cast<ABaseCharacterScript>(PC);
	if(ABCS)
	{
		PlayerCharacter = ABCS;
		UE_LOG(LogTemp,Warning,TEXT("player character ref has been set"));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("player character ref has failed"));
	}
}


// Called every frame
void UGameManagerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

