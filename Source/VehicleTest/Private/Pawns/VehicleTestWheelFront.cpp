// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "Pawns/VehicleTestWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UVehicleTestWheelFront::UVehicleTestWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}