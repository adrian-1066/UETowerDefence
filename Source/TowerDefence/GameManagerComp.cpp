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
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&UGameManagerComp::EndRound,2.0f,true);
}

TArray<AActor*> UGameManagerComp::GetAllTowers()
{
	return PlayerCharacter->TowersThatHaveBeenPlaced;
}

void UGameManagerComp::StartSetUp()
{
	SpawnEnemies();
	CurrentRound = 1;
	PlayerCharacter->HUDInstance->UpdateRoundNum(CurrentRound);
}

void UGameManagerComp::NextRoundStart()
{
	for(int i = 0; i < TotalNumOfEnemies; i++)
	{
		ListOfEnemies[i]->StartAttacking();
	}
}

void UGameManagerComp::EndRound()
{
	CurrentRound++;
	PlayerCharacter->HUDInstance->UpdateRoundNum(CurrentRound);
	for(int i = 0; i < TotalNumOfEnemies; i++)
	{
		ListOfEnemies[i]->StopAttacking();
	}
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&UGameManagerComp::NextRoundStart,2.0f,true);
	
}

void UGameManagerComp::LoseGame()
{
	if(GetWorld())
	{
		UE_LOG(LogTemp,Warning,TEXT("you have lost the game"));
		UGameplayStatics::OpenLevel(GetWorld(),"LoseGameLevel");
	}
	
}

void UGameManagerComp::WinGame()
{
	UE_LOG(LogTemp,Warning,TEXT("you have won the game"));
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
					AIConToCon->TowerToAttack = DefencePointRef;
					AIConToCon->SetGameManager(this);
					AIConToCon->Possess(SpawnedEnemy);
					SpawnedEnemy->NPCID = i;
					ListOfEnemies.Add(SpawnedEnemy);
					SpawnedEnemy->StopAttacking();
					//SpawnedEnemy->StartAttacking();
					
				}
				else
				{
					UE_LOG(LogTemp,Warning,TEXT("spawn failed"));
				}
			}
		}
		//EndRound();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&UGameManagerComp::EndRound,5.0f,true);
	}
}

void UGameManagerComp::SetPlayerCharacter()
{
	ACharacter* PC = GetWorld()->GetFirstPlayerController()->GetCharacter();
	ABaseCharacterScript* ABCS = Cast<ABaseCharacterScript>(PC);
	if(ABCS)
	{
		PlayerCharacter = ABCS;
		ABCS->CharacterSetUp();
		ABCS->GameManagerActor = GetOwner();
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

