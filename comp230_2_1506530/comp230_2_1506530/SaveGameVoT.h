// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/SaveGame.h"
#include "SaveGameVoT.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_VOT_API USaveGameVoT : public USaveGame
{
	GENERATED_BODY()
	
public:
	/**

	*/
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString PlayerName;

	/**

	*/
	UPROPERTY(VisibleAnywhere, Category = Basic)
		FString SaveSlotName;

	/**

	*/
	UPROPERTY(VisibleAnywhere, Category = Basic)
		uint32 UserIndex;

	/**

	*/
	USaveGameVoT();
	
};
