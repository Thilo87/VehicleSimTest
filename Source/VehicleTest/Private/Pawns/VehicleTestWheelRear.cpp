// Copyright Epic Games, Inc. All Rights Reserved.

#include "Pawns/VehicleTestWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UVehicleTestWheelRear::UVehicleTestWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}