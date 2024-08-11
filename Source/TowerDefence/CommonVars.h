// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "CommonVars.generated.h"

/**
 * 
 */

USTRUCT()
struct FSoundStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FString SoundName;
	UPROPERTY(EditAnywhere)
	USoundBase* SoundToPlay;
	UPROPERTY(EditAnywhere)
	bool IsSoundDiegetic;
	UPROPERTY(EditAnywhere)
	float SoundStr;
	
};

class TOWERDEFENCE_API CommonVars
{
public:
	CommonVars();
	~CommonVars();
};
