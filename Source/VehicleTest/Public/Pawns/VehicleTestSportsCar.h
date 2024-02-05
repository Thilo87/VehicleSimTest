// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VehicleTestPawn.h"
#include "VehicleTestSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class VEHICLETEST_API AVehicleTestSportsCar : public AVehicleTestPawn
{
	GENERATED_BODY()
	
public:

	AVehicleTestSportsCar();
};
