// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "Pawns/VehicleTestSportsWheelFront.h"

UVehicleTestSportsWheelFront::UVehicleTestSportsWheelFront()
{
	WheelRadius = 39.0f;
	WheelWidth = 35.0f;
	FrictionForceMultiplier = 3.0f;

	MaxBrakeTorque = 4500.0f;
	MaxHandBrakeTorque = 6000.0f;
}