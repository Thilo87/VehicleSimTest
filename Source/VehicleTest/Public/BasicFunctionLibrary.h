// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "BasicFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETEST_API UBasicFunctionLibrary : public UObject
{
	GENERATED_BODY()

	/*
	 *
	 * Conversions
	 *
	 */

	UFUNCTION( BlueprintPure, Category = "Conversions" )
	static float CentimetersPerSecondToKilometersPerHour( float CentimetersPerSecond );
};
