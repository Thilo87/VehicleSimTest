// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "Types.generated.h"

#define PRINT_SCREEN( x ) if ( GEngine ) { GEngine->AddOnScreenDebugMessage( -1, 500.0f, FColor::Yellow, x ); }

/** The name of the collision channel for obstacles */
static FName OBSTACLE_COLLISION_CHANNEL_NAME = "Obstacle";

/*
 * Phases a traffic light can have
 */
UENUM( BlueprintType )
enum class ETrafficLightPhase : uint8
{
	Red,
	RedAmber,
	Green,
	Amber
};