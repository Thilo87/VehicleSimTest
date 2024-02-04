// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TrafficRegulationActors/SpeedZone/SpeedZone.h"
#include "TrafficRegulationActors/StopZone/StopZone.h"
#include "VehicleTestUI.generated.h"

/**
 *  Simple Vehicle HUD class
 *  Displays the current speed and gear.
 *  Widget setup is handled in a Blueprint subclass.
 */
UCLASS(abstract)
class VEHICLETEST_API UVehicleTestUI : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	/** Controls the display of speed in Km/h or MPH */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Vehicle)
	bool bIsMPH = false;

public:

	/** Called to update the speed display */
	void UpdateSpeed(float NewSpeed);

	/** Called to update the gear display */
	void UpdateGear(int32 NewGear);

	void UpdateIsExceedingSpeedLimit( ASpeedZone* SpeedZone, bool bIsExceedingSpeedLimit );

	void UpdateDidNotStopLongEnoughAtStopZone( AStopZone* StopZone );

protected:

	/** Implemented in Blueprint to display the new speed */
	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnSpeedUpdate(float NewSpeed);

	/** Implemented in Blueprint to display the new gear */
	UFUNCTION(BlueprintImplementableEvent, Category = Vehicle)
	void OnGearUpdate(int32 NewGear);

	UFUNCTION( BlueprintImplementableEvent, Category = Vehicle )
	void OnIsExceedingSpeedLimitUpdate( ASpeedZone* SpeedZone, bool bIsExceedingSpeedLimit );

	UFUNCTION( BlueprintImplementableEvent, Category = Vehicle )
	void OnDidNotStopLongEnoughAtStopZone( AStopZone* StopZone );
	
};
