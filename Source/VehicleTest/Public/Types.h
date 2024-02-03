// Copyright (C) 2023-2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "Types.generated.h"

#define PRINT_SCREEN( x ) if ( GEngine ) { GEngine->AddOnScreenDebugMessage( -1, 500.0f, FColor::Yellow, x ); }

UENUM( BlueprintType )
enum class ETrafficLightPhase : uint8
{
	Red,
	RedAmber,
	Green,
	Amber
};