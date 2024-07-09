// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterScript.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
// Sets default values
ABaseCharacterScript::ABaseCharacterScript()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseCharacterScript::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacterScript::MoveInDirection(const FInputActionValue& Value)
{
	UE_LOG(LogTemp,Warning,TEXT("move action triggered"));
	FVector2D MovementDirection = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementDirection.Y);
	AddMovementInput(GetActorRightVector(), MovementDirection.X);
	
	//AddMovementInput(GetActorRightVector(),MovementDirection.X);
}

void ABaseCharacterScript::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVal = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVal.Y);
	AddControllerYawInput(LookAxisVal.X);
}

void ABaseCharacterScript::TriggerJump(const FInputActionValue& Value)
{
	
	UE_LOG(LogTemp,Warning,TEXT("Jump triggered"));
	const bool Triggered = Value.Get<bool>();
	if(Triggered)
	{
		Jump();
	}
}

// Called every frame
void ABaseCharacterScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseCharacterScript::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping,0);
		}
		
	}
	if(UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseCharacterScript::MoveInDirection);
		Input->BindAction(LookAction, ETriggerEvent::Triggered,this,&ABaseCharacterScript::Look);
		Input->BindAction(JumpAction,ETriggerEvent::Started,this,&ABaseCharacterScript::TriggerJump);
	}

}

