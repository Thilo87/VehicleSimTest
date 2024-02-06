// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "TrafficRegulationActors/Speedzone/SpeedZone.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "Pawns/VehicleTestPawn.h"
#include "PlayerControllers/VehicleTestPlayerController.h"
#include "TrafficSimulation/AiControlledCar/TrafficSimAiControlledCar.h"

void ASpeedZone::OnSpeedZoneBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// if the other actor is AI-controlled, we don't need so much functionality
	if ( ATrafficSimAiControlledCar* AiControlledCar = Cast< ATrafficSimAiControlledCar >( OtherActor ) )
	{
		AiControlledCar->OnEnteredSpeedZone( this );
		return;
	}

	if ( !PlayerController.IsValid()
		|| PlayerController->GetPawn() != OtherActor )
			return;
	
	SetActorTickEnabled( true );
	
	bIsVehicleInSpeedZone = true;
	PlayerController->OnEnteredSpeedZone( this );
}

void ASpeedZone::OnSpeedZoneEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// if the other actor is AI-controlled, we don't need so much functionality
	if ( ATrafficSimAiControlledCar* AiControlledCar = Cast< ATrafficSimAiControlledCar >( OtherActor ) )
	{
		AiControlledCar->OnLeftSpeedZone();
		return;
	}

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

ASpeedZone::ASpeedZone()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;

	RootSceneComponent = CreateDefaultSubobject< USceneComponent >( "Root" );
	RootComponent = RootSceneComponent;

	Zone = CreateDefaultSubobject< UBoxComponent >( "Zone" );
	Zone->SetupAttachment( RootSceneComponent );
}

void ASpeedZone::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast< AVehicleTestPlayerController >( GetWorld()->GetFirstPlayerController() );

	Zone->OnComponentBeginOverlap.AddDynamic( this, &ASpeedZone::OnSpeedZoneBeginOverlap );
	Zone->OnComponentEndOverlap.AddDynamic( this, &ASpeedZone::OnSpeedZoneEndOverlap );
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
