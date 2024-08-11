// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerToDefendScript.h"
#include "GameManagerComp.h"

float ATowerToDefendScript::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,
	AController* EventInstigator, AActor* DamageCauser)
{
	CurrentHealth -= DamageAmount;
	float HealthPer = (CurrentHealth/MaxHealth);//*100;
	UGameManagerComp* GameMan = Cast<UGameManagerComp>(GameManager->GetComponentByClass(UGameManagerComp::StaticClass()));
	GameMan->PlayerCharacter->HUDInstance->UpdateDefenceHealth(HealthPer);
	if(CurrentHealth <= 0.0f)
	{
		OnDeath();
	}
	return 0.0f;

}

void ATowerToDefendScript::OnDeath()
{
	UGameManagerComp* GameMan = Cast<UGameManagerComp>(GameManager->GetComponentByClass(UGameManagerComp::StaticClass()));
	if(GameMan)
	{

		GameMan->LoseGame();
	}

	Super::OnDeath();
}
