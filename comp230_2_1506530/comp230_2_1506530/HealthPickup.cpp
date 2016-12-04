// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_VoT.h"
#include "HealthPickup.h"

// Set default value
AHealthPickup::AHealthPickup()
{
	// Sets the object to simulate physics
	// when spawned
	GetMesh()->SetSimulatePhysics(true);

	// The base power level of the Health
	Health = 50.0f;
}

void AHealthPickup::WasCollected_Implementation()
{
	// Use base pickup behavior
	Super::WasCollected_Implementation();

	// Destroy the Health
	Destroy();
}

// Report the Health power level
float AHealthPickup::GetHealth()
{
	return Health;
}
