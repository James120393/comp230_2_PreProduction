// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_VoT.h"
#include "Floating.h"

// Sets default values
AFloating::AFloating()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a dummy root component we can attach things to.
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// Create a camera and a visible object
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));
	OurVisibleComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AFloating::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFloating::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Move the object up/down
void AFloating::Float(float DeltaTime)
{
	// Set up the sine wave that the function runs on
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	// Get the actor location and input
	// it into a vetor
	FVector NewLocation = GetActorLocation();

	// Set the Z vector to the new height
	NewLocation.Z += DeltaHeight * 50.0f;

	// Time for the up/down cycle to complete
	RunningTime += DeltaTime;

	// Set the actors new loacation to the 
	// location given
	SetActorLocation(NewLocation);
}

// Move the object side to side
void AFloating::FloatSide(float DeltaTime)
{
	// Set up the sine wave that the function runs on
	float DeltaHeight = (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	// Get the actor location and input
	// it into a vetor
	FVector NewLocation = GetActorLocation();

	// Set the vectors to the new height
	// and angle
	NewLocation.Z -=  Height;
	NewLocation.Y -=  AngleY;
	NewLocation.X -=  DeltaHeight * AngleX;

	// Time for the up/down cycle to complete
	RunningTime += DeltaTime;

	// Set the actors new loacation to the 
	// location given
	SetActorLocation(NewLocation);
}

// Rotate the object
void AFloating::FloatRotate(float DeltaTime)
{
	// Set up the sine wave that the function runs on
	FRotator NewRotation = GetActorRotation();

	// Set the vectors to the new height
	// and angle
	NewRotation.Pitch += DeltaTime / 50.0f;

	// Time for the rotatio  cycle to complete
	RunningTime += DeltaTime;

	// Set the actors new rotation to the 
	// rotation given
	SetActorRotation(NewRotation);
}


