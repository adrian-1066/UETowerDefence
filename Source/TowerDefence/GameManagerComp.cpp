// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManagerComp.h"


UGameManagerComp::UGameManagerComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UGameManagerComp::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerCharacter();
	StartSetUp();
	
}

TArray<AActor*> UGameManagerComp::GetAllTowers()
{
	return PlayerCharacter->TowersThatHaveBeenPlaced;
}

void UGameManagerComp::StartSetUp()
{
	CurrentRound = 1;
	CurrentRoundSize = 12;
	CurrentNPCSpawned = 0;
	NPCDefeatedThisRound = 0;
	TotalNumOfEnemies = 62;
	RoundStarted = false;
	SpawnEnemies();
	
	PlayerCharacter->HUDInstance->UpdateRoundNum(CurrentRound);
}

void UGameManagerComp::NextRoundStart()
{
	RoundStarted = true;
	if(CurrentNPCSpawned >= CurrentRoundSize)
	{
		return;
	}
	ListOfEnemies[CurrentNPCSpawned]->MaxHealth = 150 + (CurrentRound * 60);
	ListOfEnemies[CurrentNPCSpawned]->BaseMoveSpeed += 45;
	ListOfEnemies[CurrentNPCSpawned]->StartAttacking(SpawnLocations[0]->GetActorLocation());
	CurrentNPCSpawned++;
	GetWorld()->GetTimerManager().SetTimer(RoundTimer,this,&UGameManagerComp::NextRoundStart,1.0f,false);
	
}

void UGameManagerComp::EndRound()
{
	RoundStarted = false;
	CurrentRound++;
	CurrentNPCSpawned = 0;
	NPCDefeatedThisRound = 0;
	CurrentRoundSize = 12 + (CurrentRound * 4);
	PlayerCharacter->HUDInstance->UpdateRoundNum(CurrentRound);
	for(int i = 0; i < TotalNumOfEnemies; i++)
	{
		ListOfEnemies[i]->StopAttacking();
	}
	if(CurrentRound >= 11)
	{
		WinGame();
	}
	
}

void UGameManagerComp::LoseGame()
{
	if(GetWorld())
	{
		
		UGameplayStatics::OpenLevel(GetWorld(),"LoseGameLevel");
	}
	
}

void UGameManagerComp::WinGame()
{
	UGameplayStatics::OpenLevel(GetWorld(),"WinGameLevel");
}

void UGameManagerComp::NPCDeath(int NPCID)
{
	NPCDefeatedThisRound++;
	PlayerCharacter->UpdateGold(ListOfEnemies[NPCID]->MaxHealth / 10);
	if(NPCDefeatedThisRound >= CurrentRoundSize)
	{
		EndRound();
	}
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
			FVector SpawnLocation = FVector(100.0f * i + i, -1000.0f, -9800.0f);
			FRotator SpawnRotation = FRotator::ZeroRotator;
			AActor* SpawnedActor = World->SpawnActor<ABaseEnemyScript>(EnemyToSpawn, SpawnLocation, SpawnRotation, SpawnParams);

			if (SpawnedActor)
			{
				ABaseEnemyScript* SpawnedEnemy = Cast<ABaseEnemyScript>(SpawnedActor);
				if(SpawnedEnemy)
				{
					ANPCAIController* AIConToCon = GetWorld()->SpawnActor<ANPCAIController>(ANPCAIController::StaticClass());
					AIConToCon->TowerToAttack = DefencePointRef;
					AIConToCon->SetGameManager(this);
					AIConToCon->Possess(SpawnedEnemy);
					SpawnedEnemy->NPCID = i;
					ListOfEnemies.Add(SpawnedEnemy);
					SpawnedEnemy->StopAttacking();
					
					
				}
				else
				{
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
		ABCS->CharacterSetUp();
		ABCS->GameManagerActor = GetOwner();
		
	}

}



void UGameManagerComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

