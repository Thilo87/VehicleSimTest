// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpeedZone/SpeedZone.h"
#include "VehicleTestGameMode.generated.h"

UCLASS(MinimalAPI)
class AVehicleTestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AVehicleTestGameMode();

	void SetCurrentSpeedZone( ASpeedZone* SpeedZone );
};



