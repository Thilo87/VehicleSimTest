// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "UObject/Object.h"
#include "TrafficLightProperties.generated.h"

/**
 * 
 */
UCLASS()
class VEHICLETEST_API UTrafficLightProperties : public UObject
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere )
	float RedDuration = 5.f;

	UPROPERTY( EditAnywhere )
	float RedAmberDuration = 5.f;

	UPROPERTY( EditAnywhere )
	float GreenDuration = 5.f;

	UPROPERTY( EditAnywhere )
	float AmberDuration = 5.f;
};
