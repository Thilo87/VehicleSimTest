// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "UObject/Object.h"
#include "TrafficSimAiControlledCarKillVolume.generated.h"

/**
 * Volume that destroys all AI-controlled cars that enter it
 */
UCLASS()
class VEHICLETEST_API ATrafficSimAiControlledCarKillVolume : public ATriggerBox
{
	GENERATED_BODY()

public:
	ATrafficSimAiControlledCarKillVolume();
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
};
