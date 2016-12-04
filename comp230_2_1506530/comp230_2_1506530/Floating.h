// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Floating.generated.h"

UCLASS()
class PROJECT_VOT_API AFloating : public AActor
{
	GENERATED_BODY()
	
public:
	/** 
	Sets default values for this actor's properties
	*/
	AFloating();

	/**
	Called when the game starts or when spawned
	*/
	virtual void BeginPlay() override;

	/**
	Called every frame
	*/ 
	virtual void Tick(float DeltaSeconds) override;

	/**
	Visible object to reprisent the component
	*/
	UPROPERTY(EditAnywhere)
		USceneComponent* OurVisibleComponent;

protected:
	/**
	The height that the object will flaot
	*/
	UPROPERTY(EditAnywhere, Category = "Floating")
		float Height;

	/**
	An angle that the object will float
	*/
	UPROPERTY(EditAnywhere, Category = "Floating")
		float AngleY;

	/**
	An angle that the object will float
	*/
	UPROPERTY(EditAnywhere, Category = "Floating")
		float AngleX;

	/**
	The time it takes for the function to make one loop
	*/
	UPROPERTY(EditAnywhere, Category = "Floating")
		float RunningTime;

	/**
	The standard floating function to allow
	an object to float up and donw on a sin wave
	*/
	UFUNCTION(BlueprintCallable, Category = "Floating")
		void Float(float DeltaTime);

	/**
	Alloes the object to float to the side i.e. 
	left/right instead of up/down
	*/
	UFUNCTION(BlueprintCallable, Category = "Floating")
		void FloatSide(float DeltaTime);
	
	/**
	Allows the object to rotate while floating
	*/
	UFUNCTION(BlueprintCallable, Category = "Floating")
		void FloatRotate(float DeltaTime);
	
};
