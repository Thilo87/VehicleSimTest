// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleTest/Public/Speedzone/SpeedZone.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "VehicleTest/VehicleTestPawn.h"
#include "VehicleTest/VehicleTestPlayerController.h"

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

	if ( !PlayerController.IsValid() )
		return;

	SetActorTickEnabled( true );
	
	bIsVehicleInSpeedZone = true;
	PlayerController->OnEnteredSpeedZone( this );
}

void ASpeedZone::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap( OtherActor );

	if ( !PlayerController.IsValid() )
		return;

	SetActorTickEnabled( false );
	
	bIsVehicleInSpeedZone = false;
	PlayerController->OnLeftSpeedZone();
	
	if ( bIsVehicleExceedingSpeedLimit )
	{
		bIsVehicleExceedingSpeedLimit = false;
		PlayerController->OnStoppedExceedingSpeedLimit();
	}
}
