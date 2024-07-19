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
	/*if (!HorizontalBoxContainer)
	{
		HorizontalBoxContainer = ObjectInitializer.CreateDefaultSubobject<UHorizontalBox>(this, TEXT("HorizontalBoxContainer"));
	}

	if(HorizontalBoxContainer)
	{
		UE_LOG(LogTemp,Warning,TEXT("box has been made"));
	}
	CreateSlots();*/
	/*if (!IsDesignTime())
	{
		// Only create widgets at runtime, not at design time
		for (int32 i = 0; i < 5; ++i) // Adjust the number of widgets as needed
			{
			UHotBarSlotScript* NewWidget = CreateWidget<UHotBarSlotScript>(this, HotBarSlotClass);
			if (NewWidget)
			{
				BarSlots.Add(NewWidget);
			}
			}
	}*/
}

UStaticMesh* UHUDScript::GetHotBarMesh(int HotBarNum)
{
	//UStaticMeshComponent* temp = Cast<UStaticMeshComponent>(HotBarSlotsRef[HotBarNum]->TowerToSpawn);
	if(UStaticMeshComponent* temp = Cast<UStaticMeshComponent>(HotBarSlotsRef[HotBarNum]->TowerToSpawn))
	{
		UE_LOG(LogTemp,Warning,TEXT("the cast to the static mesh component %d has been successful "), HotBarNum);
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("kill yourself %d"), HotBarNum);
	}
	/*if(UStaticMesh* test = HotBarSlotsRef[HotBarNum]->GetTowerStaticMesh())
	{
		UE_LOG(LogTemp,Warning,TEXT("we gots the ref"));
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("we got no ref"));
			
		
	}*/
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
	/*if (HorizontalBoxContainer)
	{
		for (UHotBarSlotScript* Widget : BarSlots)
		{
			if (Widget)
			{
				UHorizontalBoxSlot* HorizontalBoxSlot = HorizontalBoxContainer->AddChildToHorizontalBox(Widget);
				// Optionally, you can customize the slot properties here
			}
		}
	}*/
}

void UHUDScript::CreateSlots()
{
	/*if (!HotBarSlotClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("HotBarSlotClass is not set"));
		return;
	}

	if (!HorizontalBoxContainer)
	{
		UE_LOG(LogTemp, Warning, TEXT("HorizontalBoxContainer is not bound"));
		return;
	}

	// Clear existing widgets to prevent duplication
	HorizontalBoxContainer->ClearChildren();

	// Create and add the widgets
	BarSlots.Empty();
	for (int32 i = 0; i < 5; ++i) // Adjust the number of widgets as needed
		{
		UHotBarSlotScript* NewWidget = CreateWidget<UHotBarSlotScript>(this, HotBarSlotClass);
		if (NewWidget)
		{
			BarSlots.Add(NewWidget);
			UHorizontalBoxSlot* HorizontalBoxSlot = HorizontalBoxContainer->AddChildToHorizontalBox(NewWidget);
			// Optionally, you can customize the slot properties here
		}
		}*/
}

FReply UHUDScript::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UE_LOG(LogTemp,Warning,TEXT("key has been pressed")); 
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
	UE_LOG(LogTemp, Warning, TEXT("Numeric key pressed: %d"), NumericValue);
}

void UHUDScript::ScrollHotBar(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("scroll triggered in hud Script, the value is %f"), Value.Get<float>());
	//int temp = Value.Get<float>();
	//ChangeSelected(Value.Get<float>());
}

void UHUDScript::MoveDirectToHotBar(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("direct triggered %f"), Value.Get<float>());
	//Value.GetValueTypeFromKey()
	/*if(Value.Get<bool>())
	{
		const FKey Key = Value.Get<FKey>();
		const FString KeyString = Key.ToString();

		if(KeyString.Len() == 1 && FChar::IsDigit(KeyString[0]))
		{
			int KeyValue = FCString::Atoi(*KeyString);
			UE_LOG(LogTemp, Warning, TEXT("Numeric key pressed: %d"), KeyValue);
		}
	}*/
}
