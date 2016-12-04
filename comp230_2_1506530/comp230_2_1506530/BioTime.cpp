// Fill out your copyright notice in the Description page of Project Settings.

#include "Project_VoT.h"
#include "BioTime.h"
#include "MainCharacter.h"

// Sets default values
ABioTime::ABioTime()
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
void ABioTime::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ABioTime::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}


// Allow the growth of Organic Objects
void ABioTime::Grow()
{
	bool IsAtMax = false;
	// Getting actor scale and inputting the vector into a vector
	FVector GSize = GetActorScale3D();

	// The speed that the object will grow, Hardcodded to look right
	// May expose to enging to allow more contorll
	GSize.X += 0.05f;
	GSize.Y += 0.05f;
	GSize.Z += 0.05f;

	// The main function, will only grow if the current
	// scale is smaller than the set MaxGrowth
	if (GSize.X > MaxGrowth.X)
	{
		IsAtMax = true;
	}
	else if (GSize.Y > MaxGrowth.Y)
	{
		IsAtMax = true;
	}
	else if (GSize.Z > MaxGrowth.Z)
	{
		IsAtMax = true;
	}

	if (IsAtMax == false)
	{
		SetActorScale3D(GSize);
	}
}

// Shrink objects
void ABioTime::Shrink()
{
	bool IsAtMin = false;
	// Getting actor scale and inputting the vector into a vector
	FVector SSize = GetActorScale3D();

	// The speed that the object will grow, Hardcodded to look right
	// May expose to enging to allow more contorll
	SSize.X -= 0.05f;
	SSize.Y -= 0.05f;
	SSize.Z -= 0.05f;

	// The main function, will only grow if the current
	// scale is smaller than the set MaxShrink
	if (SSize.X <= MaxShrink.X)
	{
		IsAtMin = true;
	}
	else if (SSize.Y <= MaxShrink.Y)
	{
		IsAtMin = true;
	}
	else if (SSize.Z <= MaxShrink.Z)
	{
		IsAtMin = true;
	}

	if (IsAtMin == false)
	{
		SetActorScale3D(SSize);
	}
}

// Only allow the growth of the Z axis
void ABioTime::GrowZOnly()
{
	//Getting actor scale and inputting the vector into a vector
	FVector GSize = GetActorScale3D();

	//The speed that the object will grow, Hardcodded to look right
	//May expose to enging to allow more contorll
	GSize.Z += 0.05f;

	//The main function, will only grow if the current
	//scale is smaller than the set MaxGrowth
	if (GSize.Z < MaxGrowth.Z)
	{
		SetActorScale3D(GSize);
	}
}

// Only allow Bio time to shrink on the Z axis
void ABioTime::ShrinkZOnly()
{
	//Getting actor scale and inputting the vector into a vector
	FVector SSize = GetActorScale3D();

	//The speed that the object will shrink, Hardcodded to look right
	//May expose to enging to allow more contorll
	SSize.Z -= 0.05f;

	//The main function, will only shrink if the current
	//scale is larger than the set MaxShrink
	if (SSize.Z > MaxShrink.Z)
	{
		SetActorScale3D(SSize);
	}
}

// Get the Max size the object is allowed to grow
FVector ABioTime::GetMaxSize()
{
	return MaxGrowth;
}

// Get the Min size the object is allowed to grow
FVector ABioTime::GetMinSize()
{
	return MaxShrink;
}
