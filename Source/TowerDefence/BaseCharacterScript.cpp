// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterScript.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
ABaseCharacterScript::ABaseCharacterScript()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	CurrentHotBarSlotSelected = 0;

}
// Called when the game starts or when spawned
void ABaseCharacterScript::BeginPlay()
{
	Super::BeginPlay();
	SpawnTransparentTower();

	if(HUDClass)
	{
		HUDInstance = CreateWidget<UHUDScript>(GetWorld(),HUDClass);
		if(HUDInstance)
		{
			HUDInstance->AddToViewport();
		}
	}
	HUDInstance->ChangeSelected(0);
	//UHUDScript* HudDisplay = CreateWidget<UHUDScript>(GetWorld(),UHUDScript::StaticClass());
	
}
// Called every frame
void ABaseCharacterScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Loc = GetLineTraceLocation();
	SpawnedTransparentTower->SetActorLocation(Loc);
	//TransparentTower->SetActorLocation(Loc);
	
}


void ABaseCharacterScript::ReturnLocation(FVector Loc)
{
	UE_LOG(LogTemp,Warning,TEXT("the location to display is %f %f %f"), Loc.X, Loc.Y, Loc.Z);
}



void ABaseCharacterScript::MoveInDirection(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp,Warning,TEXT("move action triggered"));
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

void ABaseCharacterScript::ScrollHotBar(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("scroll triggered in character Script, the value is %f"), Value.Get<float>());
	CurrentHotBarSlotSelected = HUDInstance->ChangeSelected(Value.Get<float>());
	TransTower->SetMesh(HUDInstance->GetHotBarMesh(CurrentHotBarSlotSelected));
}

void ABaseCharacterScript::RotatePlacement(const FInputActionValue& Value)
{
	FRotator ActorRotation = TransTower->GetActorRotation();
	ActorRotation.Add(0.0f,Value.Get<float>(),0.0f);
	TransTower->SetActorRotation(ActorRotation);
}

void ABaseCharacterScript::PlaceTower(const FInputActionValue& Value)
{
	if(TransTower->CanBePlaced)
	{
		UWorld* World = GetWorld();
		if (World)
		{
			// Define the spawn parameters
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();

			// Define the spawn location and rotation
			FVector SpawnLocation = TransTower->GetActorLocation();
			FRotator SpawnRotation = TransTower->GetActorRotation();

			// Choose the actor class to spawn
			//TSubclassOf<AActor> ActorToSpawn = AActor::StaticClass();

			// Spawn the actor
			TSubclassOf<ATowerBaseScript> TowerType = HUDInstance->TowerTypeToSpawn(CurrentHotBarSlotSelected);
			AActor* SpawnedActor = World->SpawnActor<AActor>(TowerType, SpawnLocation, SpawnRotation, SpawnParams);
			TowersThatHaveBeenPlaced.Add(SpawnedActor);
			// Check if the actor was successfully spawned
			if (SpawnedActor)
			{
				UE_LOG(LogTemp,Warning,TEXT("the test actor was spawned"));
			}
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("tower can not be placed here"));
	}
}

FVector ABaseCharacterScript::GetLineTraceLocation()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if(PlayerController)
	{
		FVector StartLocation = Camera->GetComponentLocation();
		FRotator StartRotation = Camera->GetComponentRotation();
		FVector EndLocation = StartLocation + (StartRotation.Vector() * 1000.0f);
		FCollisionQueryParams TraceParams(FName(TEXT("LineTrace")), true, this);
		TraceParams.bTraceComplex = true;
		TraceParams.bReturnPhysicalMaterial = false;

		// Perform the line trace
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility,
			TraceParams
		);
		// Draw debug line
		DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor::Green,
			false,
			1.0f,
			0,
			1.0f
		);
		if (bHit)
		{
			// Output debug information
			//UE_LOG(LogTemp,Warning,TEXT("the location that was hit %f %f %f"), HitResult.Location.X, HitResult.Location.Y, HitResult.Location.Z)
			return HitResult.Location;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *HitResult.GetActor()->GetName()));
		}

		

		
	}
	
	FVector temp = FVector::Zero();
	return temp;
}

void ABaseCharacterScript::SpawnTransparentTower()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// Define the spawn parameters
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();

		// Define the spawn location and rotation
		FVector SpawnLocation = FVector(0.0f, 0.0f, 100.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		// Choose the actor class to spawn
		//TSubclassOf<AActor> ActorToSpawn = AActor::StaticClass();

		// Spawn the actor
		AActor* SpawnedActor = World->SpawnActor<AActor>(TransTowerClass, SpawnLocation, SpawnRotation, SpawnParams);

		// Check if the actor was successfully spawned
		if (SpawnedActor)
		{
			TransTower = Cast<ABuildDisplayTowerScript>(SpawnedActor);
			TransTower->CanBePlaced = true;
			if(TransTower)
			{
				UE_LOG(LogTemp,Warning,TEXT("display tower is of type display"))
			}
			SpawnedTransparentTower = SpawnedActor;
			UE_LOG(LogTemp,Warning,TEXT("the test actor was spawned"));
			// Do something with the spawned actor (optional)
		}
	}
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
		Input->BindAction(ScrollAction, ETriggerEvent::Triggered, this, &ABaseCharacterScript::ScrollHotBar);
		Input->BindAction(RotateAction,ETriggerEvent::Triggered,this,&ABaseCharacterScript::RotatePlacement);
		Input->BindAction(PlaceTowerAction,ETriggerEvent::Started,this,&ABaseCharacterScript::PlaceTower);
	}

}

void ABaseCharacterScript::ChangeMode()
{
	if(BuildMode)
	{
		BuildMode = false;
	}
	else if(!BuildMode)
	{
		BuildMode = true;
	}
}

