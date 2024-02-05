// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "VehicleTestGameMode.h"
#include "PlayerControllers/VehicleTestPlayerController.h"

AVehicleTestGameMode::AVehicleTestGameMode()
{
	PlayerControllerClass = AVehicleTestPlayerController::StaticClass();
}
