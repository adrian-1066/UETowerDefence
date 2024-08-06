// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerToDefendScript.h"
#include "GameManagerComp.h"
void ATowerToDefendScript::OnDeath()
{
	UGameManagerComp* GameMan = Cast<UGameManagerComp>(GameManager->GetComponentByClass(UGameManagerComp::StaticClass()));
	if(GameMan)
	{
		UE_LOG(LogTemp,Warning,TEXT("game is over"));
		GameMan->LoseGame();
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("failed to get GameManager"));
	}
	Super::OnDeath();
}
