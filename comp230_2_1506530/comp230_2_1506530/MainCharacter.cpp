// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_VoT.h"
#include "MainCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AMainCharacter
//////////////////////////////////////////////////////////////////////////

AMainCharacter::AMainCharacter()
{
	//////////////////////////////////////////////////////////////////////////NOT MY CODE//////////////////////////////////////////////////////////////////////////
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

												// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

												   //Create the collection sphere
	CollectionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectionSphere"));
	CollectionSphere->SetupAttachment(RootComponent);
	CollectionSphere->SetSphereRadius(200.0f);

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

	// Set a base health for the character
	InitialHealth = 150.0f;
	CharacterHealth = InitialHealth;
	//////////////////////////////////////////////////////////////////////////NOT MY CODE//////////////////////////////////////////////////////////////////////////


	// Set the Health and Time power Variables
	Damage = -50.0f;
	HealthGainAmount = 50.0f;
	CharacterTimePower = 500.0f;
	TimePowerUsageRate = -5.0f;
}

//////////////////////////////////////////////////////////////////////////
// Input
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////NOT MY CODE//////////////////////////////////////////////////////////////////////////
void AMainCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	InputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AMainCharacter::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AMainCharacter::LookUpAtRate);

	// handle touch devices
	InputComponent->BindTouch(IE_Pressed, this, &AMainCharacter::TouchStarted);
	InputComponent->BindTouch(IE_Released, this, &AMainCharacter::TouchStopped);
}


void AMainCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	// jump, but only on the first touch
	if (FingerIndex == ETouchIndex::Touch1)
	{
		Jump();
	}
}

void AMainCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	if (FingerIndex == ETouchIndex::Touch1)
	{
		StopJumping();
	}
}

void AMainCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AMainCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
//////////////////////////////////////////////////////////////////////////NOT MY CODE//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Pickups for Health and TimePower
//////////////////////////////////////////////////////////////////////////

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::CollectPickups()
{
	// Get all overlapping actors and store them in an array
	TArray<AActor*> CollectedActors;
	CollectionSphere->GetOverlappingActors(CollectedActors);

	// For each actor we collected
	for (int32 iCollected = 0; iCollected < CollectedActors.Num(); ++iCollected)
	{
		// Cast the actor to APickup
		APickup* const TestPickup = Cast<APickup>(CollectedActors[iCollected]);

		// If the cast is successful and the pickup is valid and active
		if (TestPickup && !TestPickup->IsPendingKill() && TestPickup->IsActive())
		{
			// Call the pickups wasColected function
			TestPickup->WasCollected();
			// Check to see if the pickup is also a battery
			AHealthPickup* const TestHealth = Cast<AHealthPickup>(TestPickup);
			// Deactivate the Pickup
			TestPickup->SetActive(false);
		}
	}
}

// Increase Character Health
void AMainCharacter::HealthGain()
{
	// Get characters current health and 
	// input into current health float
	float CurrentHealth = GetCurrentHealth();

	// Check is current health is greater than 0
	// and if health is lower than 175
	if (CurrentHealth > 0 && CurrentHealth < 175.0f)// Used 175 to account small variations
	{
		// Call update health function and input
		// HealthGainAmount from uproperty
		UpdateHealth(HealthGainAmount);
	}
}

// Damage the character
void AMainCharacter::WasHitDamage()
{
	// Call upon the UpdateHealth function to
	// apply damage from the upropery
	UpdateHealth(Damage);
}

// Reports starting power
float AMainCharacter::GetInitialHealth()
{
	return InitialHealth;
}

// Reports current power
float AMainCharacter::GetCurrentHealth()
{
	return CharacterHealth;
}

// Called whenever Health is increased or decreased
// while checking if health is within range
void AMainCharacter::UpdateHealth(float HealthChange)
{
	// Checks if character health is below 175
	// if so it will increase health by given amount
	if (GetCurrentHealth() < 225.0f)
	{
		CharacterHealth = CharacterHealth + HealthChange;
	}
	// If health is above 175 or will be going above
	// 175, it will set the health back to 150
	else
	{
		CharacterHealth = 200.0f;
	}
}

// Return starting TimePower
float AMainCharacter::GetInitialTimePower()
{
	return InitialTimePower;
}

// Returns the current TimePower
float AMainCharacter::GetCurrentTimePower()
{
	return CharacterTimePower;
}

// Called whenever TimePower is increased or decreased
void AMainCharacter::UpdateTimePower(float TimePowerChange)
{
	// Checks if character health is below 525
	// if so it will increase health by given amount
	if (GetCurrentTimePower() < 525.0f)// Used 525 to account small variations
	{
		CharacterTimePower = CharacterTimePower + TimePowerChange;
	}
	// If health is above 500 or will be going above
	// 500, it will set the health back to 500
	else
	{
		CharacterTimePower = 500.0f;
	}
}

// Increase character TimePower
void AMainCharacter::TimePowerGain(float TimeGainAmount)
{
	UpdateTimePower(TimeGainAmount);
}

// Decrease character TimePower
void AMainCharacter::TimePowerUsage()
{
	UpdateTimePower(TimePowerUsageRate);
}