// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleTestWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UVehicleTestWheelFront::UVehicleTestWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}