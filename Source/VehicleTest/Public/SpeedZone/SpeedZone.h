// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "UObject/Object.h"
#include "SpeedZone.generated.h"

/**
 * 
 */
UCLASS( Category = "Speed Zone" )
class VEHICLETEST_API ASpeedZone : public ATriggerBox
{
	GENERATED_BODY()

public:
	ASpeedZone();
	
	UPROPERTY( EditAnywhere, Category = "Speed Zone|Properties" )
	float MaxSpeed = 50.f;

	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
};
