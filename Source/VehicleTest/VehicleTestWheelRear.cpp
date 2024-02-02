// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleTestWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UVehicleTestWheelRear::UVehicleTestWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}