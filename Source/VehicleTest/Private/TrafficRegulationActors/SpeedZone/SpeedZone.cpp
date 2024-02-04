// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficRegulationActors/Speedzone/SpeedZone.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "Pawns/VehicleTestPawn.h"
#include "PlayerControllers/VehicleTestPlayerController.h"

ASpeedZone::ASpeedZone()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
}

void ASpeedZone::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast< AVehicleTestPlayerController >( GetWorld()->GetFirstPlayerController() );
}

void ASpeedZone::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );
	
	if ( !PlayerController.IsValid() || !bIsVehicleInSpeedZone )
		return;

	// tell player controller if the player's vehicle exceeded the speed limit or has stopped to exceed it
	if ( const AVehicleTestPawn* Pawn = Cast< AVehicleTestPawn >( PlayerController->GetPawn() ) )
	{
		if ( !bIsVehicleExceedingSpeedLimit )
		{
			if (  FMath::Abs( Pawn->GetChaosVehicleMovement()->GetForwardSpeed() ) > SpeedLimit )
			{
				bIsVehicleExceedingSpeedLimit = true;
				PlayerController->OnStartedExceedingSpeedLimit();
			}
		}
		else
		{
			if ( FMath::Abs( Pawn->GetChaosVehicleMovement()->GetForwardSpeed() ) <= SpeedLimit )
			{
				bIsVehicleExceedingSpeedLimit = false;
				PlayerController->OnStoppedExceedingSpeedLimit();
			}
		}
	}
}

void ASpeedZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap( OtherActor );

	if ( !PlayerController.IsValid()
		|| PlayerController->GetPawn() != OtherActor )
		return;
	
	SetActorTickEnabled( true );
	
	bIsVehicleInSpeedZone = true;
	PlayerController->OnEnteredSpeedZone( this );
}

void ASpeedZone::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap( OtherActor );

	if ( !PlayerController.IsValid()
		|| PlayerController->GetPawn() != OtherActor )
		return;

	SetActorTickEnabled( false );
	
	bIsVehicleInSpeedZone = false;
	PlayerController->OnLeftSpeedZone();

	// we assume that if the player's vehicle left the speed zone, it's also "stopping to exceed the speed limit"
	if ( bIsVehicleExceedingSpeedLimit )
	{
		bIsVehicleExceedingSpeedLimit = false;
		PlayerController->OnStoppedExceedingSpeedLimit();
	}
}
