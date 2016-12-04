// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "Project_VoT.h"
#include "Project_VoTGameMode.h"

// Set defaults
AProject_VoTGameMode::AProject_VoTGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MainCharacter_BP"));

	//Set the default player pawn
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AProject_VoTGameMode::BeginPlay()
{
	Super::BeginPlay();

	// Find all spawn volume Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentState(EVoTPlayState::EPlaying);

	// Add the UI to the players screen
	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

// Called every frame
void AProject_VoTGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check that we are using the battery collector character
	AMainCharacter* MyCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		// If our Health is greater than max health set it down to 150
		if (MyCharacter->GetCurrentHealth() > MaxHealth)
		{
			MyCharacter->UpdateHealth(200.0f);
		}

		//End the Game is players healthe gets to 0 or below
		if (MyCharacter->GetCurrentHealth() <= 0)
		{
			SetCurrentState(EVoTPlayState::EGameOver);
		}
	}
}

// Returns max health
float AProject_VoTGameMode::GetMaxHealth() const
{
	return MaxHealth;
}

// Retruns max TimePower
float AProject_VoTGameMode::GetMaxTimePower() const
{
	return MaxTimePower;
}

// Returns curent PlayState
EVoTPlayState AProject_VoTGameMode::GetCurrentState() const
{
	return CurrentState;
}

// Set the current game state
void AProject_VoTGameMode::SetCurrentState(EVoTPlayState NewState)
{	
	// Set current state
	CurrentState = NewState;
	// Handle current state
	HandleNewState(CurrentState);
}

// Restart the current playstate
void AProject_VoTGameMode::SetRestart(EVoTPlayState State)
{	
	HandleNewState(State);
}

// What to do with each new state
void AProject_VoTGameMode::HandleNewState(EVoTPlayState NewState)
{
	switch (NewState)
	{
		// If the game is playing
	case EVoTPlayState::EPlaying:
	{
		// spawn volumes active
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(true);
		}
		// Block Player Input
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->SetCinematicMode(false, false, false, false, false);
		}
	}
	break;

	// If we've won the game
	case EVoTPlayState::EWon:
	{
		// Spawn Volumes Inative
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
	}
	break;

	// If the Game is lost ###################### Temp Removed some actions for debbuging 
	case EVoTPlayState::EGameOver:
	{
		// Spawn volume inactives
		//for (ASpawnVolume* Volume : SpawnVolumeActors)
		//{
		//	Volume->SetSpawningActive(false);
		//}

		// Block Player Input
		//APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		//if (PlayerController)
		//{
		//	PlayerController->SetCinematicMode(true, false, false, true, true);
		//}

		// Ragdoll character
		ACharacter* MYCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MYCharacter)
		{
			MYCharacter->GetMesh()->SetSimulatePhysics(true);
			MYCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;

	// Unknown/default state
	default:
	case EVoTPlayState::EUnknown:
	{

	}
	break;
	}
}