// Copyright (C) 2023-2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "Types.generated.h"

UENUM( BlueprintType )
enum class ETrafficLightPhase : uint8
{
	Red,
	RedAmber,
	Green,
	Amber
};