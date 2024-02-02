// Copyright Epic Games, Inc. All Rights Reserved.

#include "VehicleTestGameMode.h"
#include "VehicleTestPlayerController.h"

AVehicleTestGameMode::AVehicleTestGameMode()
{
	PlayerControllerClass = AVehicleTestPlayerController::StaticClass();
}
