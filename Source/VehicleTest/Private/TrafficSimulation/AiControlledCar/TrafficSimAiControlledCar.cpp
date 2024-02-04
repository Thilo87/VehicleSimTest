// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficSimulation/AiControlledCar/TrafficSimAiControlledCar.h"

ATrafficSimAiControlledCar::ATrafficSimAiControlledCar()
{
	GetMesh()->SetSimulatePhysics( true );
	GetMesh()->SetCollisionProfileName( FName( "Vehicle" ) );
	
	ChaosVehicleMovement = CastChecked< UChaosWheeledVehicleMovementComponent >( GetVehicleMovement() );
}
