// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "UObject/Object.h"
#include "TrafficSimPath.generated.h"

/**
 * A spline representing a path that a car can drive along
 */
UCLASS()
class VEHICLETEST_API ATrafficSimPath : public AActor
{
	GENERATED_BODY()

public:
	ATrafficSimPath();

	/** The path a car can drive along */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	TObjectPtr< USplineComponent > Spline;
};
