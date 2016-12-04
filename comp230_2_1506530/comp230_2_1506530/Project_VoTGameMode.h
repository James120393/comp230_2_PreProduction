// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "MainCharacter.h"
#include "SpawnVolume.h"
#include "GameFramework/GameMode.h"
#include "Project_VoTGameMode.generated.h"

/**
Enum to store the current state of gameplay
*/
UENUM(BlueprintType)
enum class EVoTPlayState
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class AProject_VoTGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	/**
	Set the defaults for the GameMode
	*/
	AProject_VoTGameMode();

	/**
	Function to use when something is called every frame
	*/
	virtual void Tick(float DeltaTime) override;

	/**
	Function to use to call other functions when the 
	game begins
	*/
	virtual void BeginPlay() override;

	/** 
	Returns max health - needed for the HUD 
	*/
	UFUNCTION(BlueprintPure, Category = "Health")
		float GetMaxHealth() const;

	/** 
	Returns max time power - needed for the HUD 
	*/
	UFUNCTION(BlueprintPure, Category = "TimePower")
		float GetMaxTimePower() const;
	
	/** 
	Returns the current playing state 
	*/
	UFUNCTION(BlueprintPure, Category = "GameState")
		EVoTPlayState GetCurrentState() const;

	/** 
	Sets a new playing state 
	*/
	UFUNCTION(BlueprintCallable, Category = "GameState")
	void SetCurrentState(EVoTPlayState NewState);

	/**
	Resart the game state
	*/
	UFUNCTION(BlueprintCallable, Category = "GameState")
		void SetRestart(EVoTPlayState State);

protected:
	/**
	The rate at which the character loses Health 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
		float DecayRate;

	/**
	The Health needed to win the game 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
		float MaxHealth;

	/**
	The Health needed to win the game 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "TimePower", Meta = (BlueprintProtected = "true"))
		float MaxTimePower;

	/** 
	The Widget class to use for our HUD screen 
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> HUDWidgetClass;

	/** 
	The instance of the HUD 
	*/
	UPROPERTY()
		class UUserWidget* CurrentWidget;

private:
	/**
	Keeps track of the current playing state 
	*/
	EVoTPlayState CurrentState;

	/**
	An array for all the spawn volumes to put
	the spawned actors within
	*/
	TArray<class ASpawnVolume*> SpawnVolumeActors;

	/**
	Handle any function calls that rely upon changing the playing state of our game 
	*/
	void HandleNewState(EVoTPlayState NewState);
};
