// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TrafficRegulationActors/SpeedZone/SpeedZone.h"
#include "TrafficRegulationActors/StopZone/StopZone.h"
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
	TObjectPtr< AVehicleTestPawn > VehiclePawn;

	/** Type of the UI to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf< UVehicleTestUI > VehicleUIClass;

	/** Pointer to the UI widget */
	TObjectPtr< UVehicleTestUI > VehicleUI;

	/** Speed zone the player's vehicle is currently driving in */
	UPROPERTY()
	TObjectPtr< ASpeedZone > CurrentSpeedZone;

	/** Stop zone the player's vehicle is currently driving through or stopping in */
	UPROPERTY()
	TObjectPtr< AStopZone > CurrentStopZone;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick( float Delta ) override;

	
	/** Called by a speed zone when the player has entered it */
	void OnEnteredSpeedZone( ASpeedZone* SpeedZone );
	
	/** Called by a speed zone when the player has left it */
	void OnLeftSpeedZone();

	/** Called by a speed zone when the player is exceeding the speed limit */
	void OnStartedExceedingSpeedLimit();

	/** Called by a speed zone when the player stopped to exceed the speed limit */
	void OnStoppedExceedingSpeedLimit();

	
	/** Called by a stop zone when the player has entered it */
	void OnEnteredStopZone( AStopZone* StopZone );

	/** Called by a speed zone when the player has left it */
	void OnLeftStopZone();

	/** Called by a speed zone when the player has stopped long enough in it */
	void OnStoppedLongEnough();

	/** Called by a speed zone when the player has not stopped long enough in it */
	void OnDidNotStopLongEnough();

protected:

	virtual void OnPossess( APawn* InPawn ) override;
};
