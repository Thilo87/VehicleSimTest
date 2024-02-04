// Copyright Epic Games, Inc. All Rights Reserved.


#include "PlayerControllers/VehicleTestPlayerController.h"
#include "Pawns/VehicleTestPawn.h"
#include "VehicleTestUI.h"
#include "EnhancedInputSubsystems.h"
#include "ChaosWheeledVehicleMovementComponent.h"

void AVehicleTestPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// get the enhanced input subsystem
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(InputMappingContext, 0);
	}

	// spawn the UI widget and add it to the viewport
	VehicleUI = CreateWidget<UVehicleTestUI>(this, VehicleUIClass);

	check(VehicleUI);

	VehicleUI->AddToViewport();
}

void AVehicleTestPlayerController::Tick(float Delta)
{
	Super::Tick(Delta);

	if ( IsValid(VehiclePawn) && IsValid(VehicleUI) )
	{
		VehicleUI->UpdateSpeed(VehiclePawn->GetChaosVehicleMovement()->GetForwardSpeed());
		VehicleUI->UpdateGear(VehiclePawn->GetChaosVehicleMovement()->GetCurrentGear());
	}
	
}

void AVehicleTestPlayerController::OnEnteredSpeedZone(ASpeedZone* SpeedZone)
{
	CurrentSpeedZone = SpeedZone;
}

void AVehicleTestPlayerController::OnLeftSpeedZone()
{
	CurrentSpeedZone = nullptr;
}

void AVehicleTestPlayerController::OnStartedExceedingSpeedLimit()
{
	if ( IsValid( VehicleUI ) )
		VehicleUI->UpdateIsExceedingSpeedLimit( CurrentSpeedZone, true );
}

void AVehicleTestPlayerController::OnStoppedExceedingSpeedLimit()
{
	if ( IsValid( VehicleUI ) )
		VehicleUI->UpdateIsExceedingSpeedLimit( CurrentSpeedZone, false );
}

void AVehicleTestPlayerController::OnEnteredStopZone(AStopZone* StopZone)
{
	CurrentStopZone = StopZone;
}

void AVehicleTestPlayerController::OnLeftStopZone()
{
	CurrentStopZone = nullptr;
}

void AVehicleTestPlayerController::OnStoppedLongEnough()
{
	
}

void AVehicleTestPlayerController::OnDidNotStopLongEnough()
{
	if ( IsValid( VehicleUI ) )
		VehicleUI->UpdateDidNotStopLongEnoughAtStopZone( CurrentStopZone );
}

void AVehicleTestPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// get a pointer to the controlled pawn
	VehiclePawn = CastChecked<AVehicleTestPawn>(InPawn);
}
