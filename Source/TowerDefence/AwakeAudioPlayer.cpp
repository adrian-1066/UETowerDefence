// Fill out your copyright notice in the Description page of Project Settings.


#include "AwakeAudioPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BTNode.h"

// Sets default values for this component's properties
UAwakeAudioPlayer::UAwakeAudioPlayer()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UAwakeAudioPlayer::BeginPlay()
{
	Super::BeginPlay();
	TheActor = this->GetOwner();
	DefaultSceneComponent = TheActor->GetRootComponent();
	if(DefaultSceneComponent)
	{
		UE_LOG(LogTemp,Warning,TEXT("awake audio component has gotten a reference to the root scene comp"));
	}
	CreateAudioComponents();
	//SoundComponents[0]->Play();
	//SoundComponents[1]->Play();
	UE_LOG(LogTemp,Warning,TEXT("there %d sound comps in the sound comp list"), SoundComponents.Num());
}


void UAwakeAudioPlayer::CreateAudioComponents()
{
	for(int i = 0; i < ListOfSounds.Num(); i++)
	{
		UE_LOG(LogTemp,Warning,TEXT("creating audio comp %d"), i);
		if(UAudioComponent* AudioComponentToAdd = NewObject<UAudioComponent>(TheActor, UAudioComponent::StaticClass(), FName(*FString::Printf(TEXT("SoundComponent%d"), i))))
		{
			AudioComponentToAdd->RegisterComponent();
			//AudioComponentToAdd->OnComponentCreated();
			AudioComponentToAdd->AttachToComponent(DefaultSceneComponent, FAttachmentTransformRules::KeepRelativeTransform);
			TheActor->AddInstanceComponent(AudioComponentToAdd);
			UE_LOG(LogTemp,Warning,TEXT("audio comp %d has been created"), i);
			AudioComponentToAdd->Sound = ListOfSounds[i].SoundToPlay;
			SoundComponents.Add(AudioComponentToAdd);
		}
		else
		{
			UE_LOG(LogTemp,Warning,TEXT("failed to create a sound component for sound %d"), i);
			
		}
	}
}




void UAwakeAudioPlayer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UAwakeAudioPlayer::PlaySound(FString SoundToPlay)
{

	bool SoundFound = false;
	for(int i = 0; i < ListOfSounds.Num(); i++)
	{
		if(ListOfSounds[i].SoundName == SoundToPlay)
		{
			SoundComponents[i]->Play();
			SoundFound = true;
			
		}
	}

	if(!SoundFound)
	{
		UE_LOG(LogTemp, Warning,TEXT("no sound was found with the name %s"), *SoundToPlay);
	}
}

void UAwakeAudioPlayer::PlaySoundByIndex(int SoundIndex)
{
	SoundComponents[SoundIndex]->Play();
}

void UAwakeAudioPlayer::PauseAllSoundFromActor()
{
	for(int i = 0; i < SoundComponents.Num();i++)
	{
		if(SoundComponents[i]->IsPlaying())
		{
			SoundComponents[i]->SetPaused(true);
		}
	}
}

void UAwakeAudioPlayer::UnPauseAllSoundFromActor()
{
	for(int i = 0; i < SoundComponents.Num();i++)
	{
		SoundComponents[i]->SetPaused(false);
	}
}

void UAwakeAudioPlayer::PauseSetSound(int SoundIndex)
{
	SoundComponents[SoundIndex]->SetPaused(true);
}

void UAwakeAudioPlayer::StopPlayingSound(int SoundIndex)
{
	
	SoundComponents[SoundIndex]->Stop();
}
