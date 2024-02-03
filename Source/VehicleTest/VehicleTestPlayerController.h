// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpeedZone/SpeedZone.h"
#include "StopZone/StopZone.h"
#include "VehicleTestPlayerController.generated.h"

class UInputMappingContext;
class AVehicleTestPawn;
class UVehicleTestUI;

/**
 *  Vehicle Player Controller class
 *  Handles input mapping and user interface
 */
UCLASS(abstract)
class VEHICLETEST_API AVehicleTestPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	/** Input Mapping Context to be used for player input */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	/** Pointer to the controlled vehicle pawn */
	TObjectPtr<AVehicleTestPawn> VehiclePawn;

	/** Type of the UI to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<UVehicleTestUI> VehicleUIClass;

	/** Pointer to the UI widget */
	TObjectPtr<UVehicleTestUI> VehicleUI;

	/** Speed zone the player's vehicle is currently driving in */
	UPROPERTY()
	ASpeedZone* CurrentSpeedZone;

	UPROPERTY()
	AStopZone* CurrentStopZone;

	// Begin Actor interface
protected:

	virtual void BeginPlay() override;

public:
	virtual void Tick(float Delta) override;
	
	void OnEnteredSpeedZone( ASpeedZone* SpeedZone );
	void OnLeftSpeedZone();
	void OnStartedExceedingSpeedLimit();
	void OnStoppedExceedingSpeedLimit();


	void OnEnteredStopZone( AStopZone* StopZone );
	void OnLeftStopZone();
	void OnStoppedLongEnough();
	void OnDidNotStopLongEnough();
	

	// End Actor interface

	// Begin PlayerController interface
protected:

	virtual void OnPossess(APawn* InPawn) override;

	// End PlayerController interface
};
