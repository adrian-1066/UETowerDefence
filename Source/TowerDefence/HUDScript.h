// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "HotBarSlotScript.h"
#include "Components/HorizontalBox.h"
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
	/*UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Widgets",meta = (BindWidget))
	UHorizontalBox* HorizontalBoxContainer;*/
	
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	void AddHotBarSlots(UHotBarSlotScript* HotBarSlot);
	UPROPERTY()
	TArray<UHotBarSlotScript*> HotBarSlotsRef;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Stats")
	int SelectedHotBarOption;
	int HotBarSize;
	UFUNCTION(BlueprintCallable, Category="Stats")
	void SetNumOfSlots(int Total);
	
	int ChangeSelected(int Direction);

	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
	void HighlightOption(int Option, int PreviousHighlight);

	UHUDScript(const FObjectInitializer& ObjectInitializer);

	UStaticMesh* GetHotBarMesh(int HotBarNum);

	TSubclassOf<ATowerBaseScript> TowerTypeToSpawn(int HotBarNum);  

	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TArray<UHotBarSlotScript*> BarSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UHotBarSlotScript> HotBarSlotClass;*/

	virtual void PostLoad() override;

private:
	void CreateSlots();
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
