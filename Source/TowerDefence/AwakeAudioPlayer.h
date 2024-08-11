#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "CommonVars.h"
#include "Components/AudioComponent.h"
#include "AwakeAudioPlayer.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENCE_API UAwakeAudioPlayer : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAwakeAudioPlayer();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	UPROPERTY()
	USceneComponent* DefaultSceneComponent;
	

	void CreateAudioComponents();
	
	
	UPROPERTY()
	AActor* TheActor;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void PlaySound(FString SoundToPlay);
	UFUNCTION(BlueprintCallable)
	void PlaySoundByIndex(int SoundIndex);
	UFUNCTION(BlueprintCallable)
	void PauseAllSoundFromActor();
	UFUNCTION(BlueprintCallable)
	void UnPauseAllSoundFromActor();
	UFUNCTION(BlueprintCallable)
	void PauseSetSound(int SoundIndex);
	UFUNCTION(BlueprintCallable)
	void StopPlayingSound(int SoundIndex);
	UPROPERTY()
	TArray<UAudioComponent*> SoundComponents;
	
	//actor to play sound on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Audio")
	AActor* ActorTarget;
	//sounds to play
	UPROPERTY(EditAnywhere, Category="Audio")
	TArray<FSoundStruct> ListOfSounds;
	
		
};
