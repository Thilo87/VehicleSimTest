// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "TrafficRegulationActors/StopZone/StopZone.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "Pawns/VehicleTestPawn.h"
#include "PlayerControllers/VehicleTestPlayerController.h"
#include "TrafficSimulation/AiControlledCar/TrafficSimAiControlledCar.h"

AStopZone::AStopZone()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void AStopZone::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast< AVehicleTestPlayerController >( GetWorld()->GetFirstPlayerController() );
}

void AStopZone::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );

	if ( !PlayerController.IsValid() )
		return;

	const AVehicleTestPawn* Pawn = Cast< AVehicleTestPawn >( PlayerController->GetPawn() );
	if ( !IsValid( Pawn ) )
		return;
	
	if ( FMath::Abs( Pawn->GetChaosVehicleMovement()->GetForwardSpeed() ) < 0.1f )
		DurationVehicleInStopZoneAtZeroSpeed += DeltaSeconds;
	else
		DurationVehicleInStopZoneAtZeroSpeed = 0.f;
	
	if ( DurationVehicleInStopZoneAtZeroSpeed >= MinStopDuration )
	{
		SetActorTickEnabled( false );
		bStoppedLongEnough = true;
		
		PlayerController->OnStoppedLongEnough();
	}
}

void AStopZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap( OtherActor );
	
	// TODO: also AI controlled cars should be aware of how long they were in the stop zone
	if ( ATrafficSimAiControlledCar* AiControlledCar = Cast< ATrafficSimAiControlledCar >( OtherActor ) )
	{
		AiControlledCar->OnEnteredStopZone( this );
		return;
	}

	if ( !PlayerController.IsValid()
		|| PlayerController->GetPawn() != OtherActor )
		return;

	SetActorTickEnabled( true );
	bIsVehicleInStopZone = true;

	PlayerController->OnEnteredStopZone( this );
}

void AStopZone::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap( OtherActor );

	if ( ATrafficSimAiControlledCar* AiControlledCar = Cast< ATrafficSimAiControlledCar >( OtherActor ) )
	{
		AiControlledCar->OnLeftStopZone( this );
		return;
	}
	
	if ( !PlayerController.IsValid()
		|| PlayerController->GetPawn() != OtherActor )
		return;

	// we want to call events only after all changes to this actor have been made
	const bool bOldStoppedLongEnough = bStoppedLongEnough;

	SetActorTickEnabled( false );
	bIsVehicleInStopZone = false;
	DurationVehicleInStopZoneAtZeroSpeed = 0.f;
	bStoppedLongEnough = false;
	
	if ( !bOldStoppedLongEnough )
		PlayerController->OnDidNotStopLongEnough();

	PlayerController->OnLeftStopZone();
}

