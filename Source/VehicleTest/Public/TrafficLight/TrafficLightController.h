// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrafficLight.h"
#include "TrafficLightProperties.h"
#include "GameFramework/Actor.h"
#include "TrafficLightController.generated.h"

USTRUCT( BlueprintType )
struct FTrafficLightWithProperties
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	ATrafficLight* TrafficLightActor;

	UPROPERTY( EditAnywhere )
	UTrafficLightProperties* TrafficLightProperties;
};

UCLASS( abstract, Category = "Traffic Light Controller" )
class VEHICLETEST_API ATrafficLightController : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY( EditAnywhere, Category = "Traffic Light Controller" )
	TArray< FTrafficLightWithProperties > TrafficLights;
};
