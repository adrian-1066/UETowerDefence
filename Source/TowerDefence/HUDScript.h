// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HUDScript.generated.h"

/**
 * 
 */

UCLASS()
class TOWERDEFENCE_API UHUDScript : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativeConstruct() override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	int SelectedHotBarOption;
	int HotBarSize;
	UFUNCTION(BlueprintCallable, Category="Stats")
	void SetNumOfSlots(int Total);
	
	void ChangeSelected(int Direction);

	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
	void HighlightOption(int Option, int PreviousHighlight);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* ScrollAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DirectSelectionAction;

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;


	void ScrollHotBar(const FInputActionValue& Value);
	void MoveDirectToHotBar(const FInputActionValue& Value);
	void HandleNumKey(const FKey& Key);
	
};
