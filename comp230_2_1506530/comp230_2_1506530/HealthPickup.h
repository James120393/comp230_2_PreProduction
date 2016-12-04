// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class PROJECT_VOT_API AHealthPickup : public APickup
{
	GENERATED_BODY()

public:
	/** 
	Sets default values for this actor's properties
	*/
	AHealthPickup();

	/** 
	Override the WasCollected Function - use Implementation becasue it's a Blueprint Native Event 
	*/
	void WasCollected_Implementation() override;

	/** 
	Public way to access the health level 
	*/
	float GetHealth();
	
protected:
	/** 
	Set the amount of power the battery gives to the chatacter 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
		float Health;
};

