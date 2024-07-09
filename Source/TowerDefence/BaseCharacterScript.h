// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "BaseCharacterScript.generated.h"

UCLASS()
class TOWERDEFENCE_API ABaseCharacterScript : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacterScript();
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category="Enhanced Input")
	class UInputMappingContext* InputMapping;
	UPROPERTY(EditAnywhere,Category="Enhanced Input")
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, Category="Enhanced Input")
	class UInputAction* LookAction;
	UPROPERTY(EditAnywhere,Category="Enhanced Input")
	class UInputAction* JumpAction;

	virtual void MoveInDirection(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void TriggerJump(const FInputActionValue& Value);
	

};
