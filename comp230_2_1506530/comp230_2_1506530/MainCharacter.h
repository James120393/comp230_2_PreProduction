// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Pickup.h"
#include "HealthPickup.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	/** 
	Camera boom positioning the camera behind the character 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** 
	Follow camera 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;

	/** 
	Collection Sphere 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* CollectionSphere;

	/**
	Character mesh
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UMeshComponent* CharacterMesh;

public:
	/**
	Set up defaults for the main character
	*/
	AMainCharacter();

	/** 
	Base turn rate, in deg/sec. Other scaling may affect final turn rate. 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	/** 
	Base look up/down rate, in deg/sec. Other scaling may affect final rate. 
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/** 
	Called when the character is hit by something that causes damage
	*/
	UFUNCTION(BlueprintCallable, Category = "Hit")
		void WasHitDamage();

	/** 
	Called when we press a key to collect any pickups inside the collection sphere
	*/
	UFUNCTION(BlueprintCallable, Category = "Pickups")
		void CollectPickups();

	/**
	Called when character gains health
	*/
	UFUNCTION(BlueprintCallable, Category = "Health")
		void HealthGain();

	/** 
	Accessor function for initail Health 
	*/
	UFUNCTION(BlueprintPure, Category = "Health")
		float  GetInitialHealth();

	/** 
	Accessor function for current Health 
	*/
	UFUNCTION(BlueprintPure, Category = "Health")
		float  GetCurrentHealth();

	/**
	Function to update the character's Health
	@param HealthChange This is the amount to change by, and it can be positive or negative.
	*/
	UFUNCTION(BlueprintCallable, Category = "Health")
		void UpdateHealth(float HealthChange);

	/**
	Accessor function for initail TimePower
	*/
	UFUNCTION(BlueprintPure, Category = "TimePower")
		float  GetInitialTimePower();

	/**
	Accessor function for current TimePower
	*/
	UFUNCTION(BlueprintPure, Category = "TimePower")
		float  GetCurrentTimePower();

	/**
	Function to update the character's TimePower
	@param TimePowerChange This is the amount to change by, and it can be positive or negative.
	*/
	UFUNCTION(BlueprintCallable, Category = "TimePower")
		void UpdateTimePower(float TimePowerChange);

	/** 
	Gain TimePower
	*/
	UFUNCTION(BlueprintCallable, Category = "TimePower")
		void TimePowerGain(float Amount);

	/**
	Use TimePower
	*/
	UFUNCTION(BlueprintCallable, Category = "TimePower")
		void TimePowerUsage();

protected:
	/** 
	Called for forwards/backward input 
	*/
	void MoveForward(float Value);

	/** 
	Called for side to side input 
	*/
	void MoveRight(float Value);

	/**
	Called via input to turn at a given rate.
	@param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void TurnAtRate(float Rate);

	/**
	Called via input to turn look up/down at a given rate.
	@param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	*/
	void LookUpAtRate(float Rate);

	/** 
	Handler for when a touch input begins 
	*/
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** 
	Handler for when a touch input stops 
	*/
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	/**
	APawn interface
	*/
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	/** 
	Float for storing the character initail
	starting Health
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
		float InitialHealth;

	/**
	Float for storing the amount of health given the the
	character when they pick up health
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", Meta = (BlueprintProtected = "true"))
		float HealthGainAmount;

	/**
	Float for storing the amount of damage given the the
	character when they get hit
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", Meta = (BlueprintProtected = "true"))
		float Damage;

	/**
	Float for storing the amount of health given the the
	character when they pick up TimePower
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePower", Meta = (BlueprintProtected = "true"))
		float TimePowerPickup;

	/**
	Float for storing the character initail 
	starting TimePower
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePower", Meta = (BlueprintProtected = "true"))
		float InitialTimePower;

	/**
	Float for storing the Usage rate of
	TimePower during gameplay, can be changed in
	engine
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TimePower", Meta = (BlueprintProtected = "true"))
		float TimePowerUsageRate;

private:
	/** 
	Float that coontains the current h
	Health level of our character 
	*/
	UPROPERTY(VisibleAnywhere, Category = "Health")
		float CharacterHealth;
	
	/**
	Float that contains the current TimePower 
	level of out character
	*/
	UPROPERTY(VisibleAnywhere, Category = "TimePower")
		float CharacterTimePower;

	/**
	Called every frame
	*/
	virtual void Tick(float DeltaSeconds) override;

public:
	/** 
	Returns CameraBoom subobject 
	**/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/**
	Returns FollowCamera subobject 
	**/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	/** 
	Returns CollectiionSphere subobject
	**/
	FORCEINLINE class USphereComponent* GetCollectionSphere() const { return CollectionSphere; }
};

