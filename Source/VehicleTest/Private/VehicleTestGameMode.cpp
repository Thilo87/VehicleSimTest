// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleTestGameMode.h"
#include "PlayerControllers/VehicleTestPlayerController.h"

AVehicleTestGameMode::AVehicleTestGameMode()
{
	PlayerControllerClass = AVehicleTestPlayerController::StaticClass();
}

void AVehicleTestGameMode::SetCurrentSpeedZone(ASpeedZone* SpeedZone)
{
	
}
