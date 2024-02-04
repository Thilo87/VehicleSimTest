// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficSimulation/TrafficSimPath.h"

ATrafficSimPath::ATrafficSimPath()
{
	PrimaryActorTick.bCanEverTick = true;

	Spline = CreateDefaultSubobject< USplineComponent >( TEXT( "Spline" ) );
	RootComponent = Spline;
}
