// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SplineComponent.h"
#include "UObject/Object.h"
#include "TrafficSimPath.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETEST_API ATrafficSimPath : public AActor
{
	GENERATED_BODY()



public:
	ATrafficSimPath();

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly )
	USplineComponent* Spline;
};
