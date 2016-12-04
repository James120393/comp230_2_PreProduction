// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BioTime.generated.h"

UCLASS()
class PROJECT_VOT_API ABioTime : public AActor
{
	GENERATED_BODY()
	
public:	
	/** 
	Sets default values for this actor's properties
	*/
	ABioTime();

	/** 
	Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;
	
	/**
	Called every frame
	*/
	virtual void Tick( float DeltaSeconds ) override;

	/**
	Visible object to reprisent the component
	*/
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;

	/** 
	Function to allow the growth of an organic objects.
	It takes a max growth Vector which is set by the designers in engine.
	*/
	UFUNCTION(BlueprintCallable, Category = "BioTime")
	void Grow();

	/**
	Function to allow the growth of an organic objects.
	It takes a max growth Vector which is set by the designers in engine.
	Will only increase the Z Vector.
	*/
	UFUNCTION(BlueprintCallable, Category = "BioTime")
		void GrowZOnly();

	/**
	Function that allows the shrinking of organic objects.
	It takes a min growth Vector which is set by the designers in engine.
	*/
	UFUNCTION(BlueprintCallable, Category = "BioTime")
		void Shrink();

	/**
	Function that allows the shrinking of organic objects.
	It takes a min growth Vector which is set by the designers in engine.
	Will only lower the Z Vector.
	*/
	UFUNCTION(BlueprintCallable, Category = "BioTime")
		void ShrinkZOnly();

	/**
	This function is to get the max size that bio time
	can grow, this float is set in engine.
	*/
	UFUNCTION(BlueprintCallable, Category = "BioTime")
		FVector GetMaxSize();

	/**
	This function is to get the min size that bio time
	can grow, this float is set in engine.
	*/
	UFUNCTION(BlueprintCallable, Category = "BioTime")
		FVector GetMinSize();


protected:
	/**
	Here we are setting up the Max variables for each organic object.
	They will not grow beyond the values set.
	Exposing them to the editor allows the designer to have full controll over each instance.
	*/
	UPROPERTY(EditAnywhere, Category = "BioTime")
		FVector MaxGrowth;

	/**
	Here we are setting up the Min variables for each organic object.
	They will not shrink beyond the values set.
	Exposing them to the editor allows the designer to have full controll over each instance.
	*/
	UPROPERTY(EditAnywhere, Category = "BioTime")
		FVector MaxShrink;

};
