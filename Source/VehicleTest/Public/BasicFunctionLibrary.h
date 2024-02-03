// Fill out your copyright notice in the Description page of Project Settings.

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
