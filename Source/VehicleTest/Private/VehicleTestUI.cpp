// Copyright Epic Games, Inc. All Rights Reserved.


#include "VehicleTestUI.h"

void UVehicleTestUI::UpdateSpeed(float NewSpeed)
{
	// format the speed to KPH or MPH
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);
	
	OnSpeedUpdate( FormattedSpeed );
}

void UVehicleTestUI::UpdateGear(int32 NewGear)
{
	OnGearUpdate(NewGear);
}

void UVehicleTestUI::UpdateIsExceedingSpeedLimit(ASpeedZone* SpeedZone, bool bIsExceedingSpeedLimit)
{
	OnIsExceedingSpeedLimitUpdate( SpeedZone, bIsExceedingSpeedLimit );
}

void UVehicleTestUI::UpdateDidNotStopLongEnoughAtStopZone(AStopZone* StopZone)
{
	OnDidNotStopLongEnoughAtStopZone( StopZone );
}
