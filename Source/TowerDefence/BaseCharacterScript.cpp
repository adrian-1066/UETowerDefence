// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacterScript.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameManagerComp.h"
#include "UObject/ConstructorHelpers.h"
// Sets default values
ABaseCharacterScript::ABaseCharacterScript()
{

	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	CurrentHotBarSlotSelected = 0;

}


void ABaseCharacterScript::UpdateGold(int Value)
{
	Gold += Value;
	HUDInstance->UpdateGoldText(Gold);
}


void ABaseCharacterScript::BeginPlay()
{
	Super::BeginPlay();
	AudioPlayer = FindComponentByClass<UAwakeAudioPlayer>();
	if(AudioPlayer)
	{
		UE_LOG(LogTemp,Warning,TEXT("found audio"));
	}
	SpawnTransparentTower();

	
	
	
}
void ABaseCharacterScript::CharacterSetUp()
{
	if(HUDClass)
	{
		HUDInstance = CreateWidget<UHUDScript>(GetWorld(),HUDClass);
		if(HUDInstance)
		{
			HUDInstance->AddToViewport();
		}
	}
	HUDInstance->ChangeSelected(0);
	UpdateGold(500);

}

void ABaseCharacterScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector Loc = GetLineTraceLocation();
}


void ABaseCharacterScript::ReturnLocation(FVector Loc)
{
	//UE_LOG(LogTemp,Warning,TEXT("the location to display is %f %f %f"), Loc.X, Loc.Y, Loc.Z);
}



void ABaseCharacterScript::MoveInDirection(const FInputActionValue& Value)
{

	FVector2D MovementDirection = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementDirection.Y);
	AddMovementInput(GetActorRightVector(), MovementDirection.X);
	
	
}

void ABaseCharacterScript::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVal = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVal.Y);
	AddControllerYawInput(LookAxisVal.X);
}

void ABaseCharacterScript::TriggerJump(const FInputActionValue& Value)
{
	const bool Triggered = Value.Get<bool>();
	if(Triggered)
	{
		Jump();
	}
}

void ABaseCharacterScript::ScrollHotBar(const FInputActionValue& Value)
{
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
			TSubclassOf<ATowerBaseScript> TowerType = HUDInstance->TowerTypeToSpawn(CurrentHotBarSlotSelected);
			if(Gold < TowerType.GetDefaultObject()->GoldCost)
			{
				return;
			}

			UpdateGold(-TowerType.GetDefaultObject()->GoldCost);
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			FVector SpawnLocation = TransTower->GetActorLocation();
			FRotator SpawnRotation = TransTower->GetActorRotation();
			AActor* SpawnedActor = World->SpawnActor<AActor>(TowerType, SpawnLocation, SpawnRotation, SpawnParams);
			TowersThatHaveBeenPlaced.Add(SpawnedActor);
		}
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
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartLocation,
			EndLocation,
			ECC_Visibility,
			TraceParams
		);
		// Draw debug line
		/*DrawDebugLine(
			GetWorld(),
			StartLocation,
			EndLocation,
			FColor::Green,
			false,
			1.0f,
			0,
			1.0f
		);*/
		if (bHit)
		{
			SpawnedTransparentTower->SetActorLocation(HitResult.Location);
			TransTower->CanBePlaced = true;
			return HitResult.Location;
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Hit: %s"), *HitResult.GetActor()->GetName()));
		}
		
	}

	TransTower->CanBePlaced = false;
	SpawnedTransparentTower->SetActorLocation(FVector(-1000.0f,-1000.0f,10000.0f));
	FVector temp = FVector::Zero();
	return temp;
}

void ABaseCharacterScript::SpawnTransparentTower()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		FVector SpawnLocation = FVector(0.0f, 0.0f, 100.0f);
		FRotator SpawnRotation = FRotator::ZeroRotator;
		AActor* SpawnedActor = World->SpawnActor<AActor>(TransTowerClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (SpawnedActor)
		{
			TransTower = Cast<ABuildDisplayTowerScript>(SpawnedActor);
			TransTower->CanBePlaced = true;
			SpawnedTransparentTower = SpawnedActor;
		}
	}
}

void ABaseCharacterScript::StartNextRound()
{
	UGameManagerComp* GameManager = Cast<UGameManagerComp>(GameManagerActor->GetComponentByClass(UGameManagerComp::StaticClass()));
	if(GameManager)
	{
		if(GameManager->RoundStarted)
		{
			return;
		}
		GameManager->NextRoundStart();
	}
}


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
		Input->BindAction(StartNextRoundAction,ETriggerEvent::Triggered,this,&ABaseCharacterScript::StartNextRound);
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

