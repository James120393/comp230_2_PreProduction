// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_VoT.h"
#include "Pickup.h"


APickup::APickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// All Pickups are active
	bIsActive = true;

	// Create the Static Mesh component 
	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	RootComponent = PickupMesh;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Returns active state
bool APickup::IsActive()
{
	return bIsActive;
}

// Changes active state
void APickup::SetActive(bool NewPickupState)
{
	bIsActive = NewPickupState;
}

// Function to call when the pickup is collected 
void APickup::WasCollected_Implementation()
{
	// Log a debug message
	FString PickupDebugString = GetName();
	UE_LOG(LogClass, Log, TEXT("You Have Collected %s"), *PickupDebugString);
}

