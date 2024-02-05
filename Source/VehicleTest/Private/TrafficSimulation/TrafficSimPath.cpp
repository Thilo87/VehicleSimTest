// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "TrafficSimulation/TrafficSimPath.h"

ATrafficSimPath::ATrafficSimPath()
{
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject< USplineComponent >( TEXT( "Spline" ) );
	RootComponent = Spline;
}
