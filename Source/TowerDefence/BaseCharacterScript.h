// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h" 
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "HUDScript.h"
#include "BuildDisplayTowerScript.h"
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

	UPROPERTY(EditAnywhere, Category = "Components")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditAnywhere, Category = "Components")
	UCameraComponent* Camera = nullptr;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Player State")
	bool BuildMode;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tower Builder")
	TSubclassOf<AActor> TransparentTower;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tower Builder")
	TSubclassOf<ABuildDisplayTowerScript> TransTowerClass;

	UPROPERTY()
	AActor* SpawnedTransparentTower;
	UPROPERTY()
	ABuildDisplayTowerScript* TransTower;

	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
	void GetLocation();

	UFUNCTION(BlueprintCallable, Category="Tower Builder")
	void ReturnLocation(FVector Loc);
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
	UPROPERTY(EditAnywhere,Category="Enhanced Input")
	class UInputAction* ScrollAction;

	virtual void MoveInDirection(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void TriggerJump(const FInputActionValue& Value);
	virtual void ScrollHotBar(const FInputActionValue& Value);

	FVector GetLineTraceLocation();
	void SpawnTransparentTower();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UHUDScript> HUDClass;

	int CurrentHotBarSlotSelected;

private:
	UPROPERTY()
	UHUDScript* HUDInstance;

};
