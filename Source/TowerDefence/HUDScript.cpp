// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDScript.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"




void UHUDScript::NativeConstruct()
{
	Super::NativeConstruct();
	//bIsFocusable = true;
	SetIsFocusable(true);
	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 1);

			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				// Bind input actions
				EnhancedInputComponent->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &UHUDScript::ScrollHotBar);
				EnhancedInputComponent->BindAction(DirectSelectionAction, ETriggerEvent::Triggered, this, &UHUDScript::MoveDirectToHotBar);
			}
		}
	}
	SelectedHotBarOption = 0;
	//ChangeSelected(0);
}

void UHUDScript::AddHotBarSlots(UHotBarSlotScript* HotBarSlot)
{
	HotBarSlotsRef.Add(HotBarSlot);
}


void UHUDScript::SetNumOfSlots(int Total)
{
	HotBarSize = Total;
	UE_LOG(LogTemp,Warning,TEXT("the size of the hot bar is %d"),HotBarSize);
}

int UHUDScript::ChangeSelected(int Direction)
{
	int tempNewSelection = SelectedHotBarOption + Direction;

	if(tempNewSelection < 0)
	{
		tempNewSelection = HotBarSize - 1;
	}
	else if(tempNewSelection >= HotBarSize)
	{
		tempNewSelection = 0;
	}
	HighlightOption(tempNewSelection, SelectedHotBarOption);
	SelectedHotBarOption = tempNewSelection;
	return SelectedHotBarOption;
	
}

UHUDScript::UHUDScript(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

UStaticMesh* UHUDScript::GetHotBarMesh(int HotBarNum)
{
	
	
	UStaticMesh* test = HotBarSlotsRef[HotBarNum]->GetTowerStaticMesh();
	return test;
}

TSubclassOf<ATowerBaseScript> UHUDScript::TowerTypeToSpawn(int HotBarNum)
{
	return HotBarSlotsRef[HotBarNum]->TowerToSpawn;
}


void UHUDScript::PostLoad()
{
	Super::PostLoad();
	
}

void UHUDScript::CreateSlots()
{
	
}

FReply UHUDScript::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	
	const FKey Key = InKeyEvent.GetKey();
	const FString KeyString = Key.ToString();

	if (KeyString.Len() == 1 && FChar::IsDigit(KeyString[0]))
	{
		HandleNumKey(Key);
		return FReply::Handled();
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UHUDScript::HandleNumKey(const FKey& Key)
{
	const FString KeyString = Key.ToString();
	int NumericValue = FCString::Atoi(*KeyString);

}

void UHUDScript::ScrollHotBar(const FInputActionValue& Value)
{

}

void UHUDScript::MoveDirectToHotBar(const FInputActionValue& Value)
{

}
