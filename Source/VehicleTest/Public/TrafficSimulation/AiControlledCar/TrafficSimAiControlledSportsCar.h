// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TrafficSimAiControlledCar.h"
#include "UObject/Object.h"
#include "TrafficSimAiControlledSportsCar.generated.h"

/**
 * AI-controlled sports car
 */
UCLASS()
class VEHICLETEST_API ATrafficSimAiControlledSportsCar : public ATrafficSimAiControlledCar
{
	GENERATED_BODY()

public:
	ATrafficSimAiControlledSportsCar();
};
