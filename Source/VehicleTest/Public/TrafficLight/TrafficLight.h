// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Types.h"
#include "TrafficLight.generated.h"

UCLASS()
class VEHICLETEST_API ATrafficLight : public AActor
{
	GENERATED_BODY()

public:
	// void SetTrafficLightPhase( ETrafficLightPhase NewTrafficLightPhase );
	// void SwitchToNextPhase();

	UFUNCTION( BlueprintImplementableEvent )
	void OnTrafficLightPhaseChanged( ETrafficLightPhase NewTrafficLightPhase );
};
