// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrafficRegulationActors/SpeedZone/SpeedZone.h"
#include "VehicleTestGameMode.generated.h"

UCLASS( MinimalAPI )
class AVehicleTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVehicleTestGameMode();
};



