// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "UObject/Object.h"
#include "SpeedZone.generated.h"

class AVehicleTestPlayerController;

/**
 * Actor for a speed zone with a speed limit
 */
UCLASS( Category = "Speed Zone" )
class VEHICLETEST_API ASpeedZone : public ATriggerBox
{
	GENERATED_BODY()

	/** Pointer to the player controller */
	TWeakObjectPtr< AVehicleTestPlayerController > PlayerController;

	/** If the player's vehicle is currently exceeding the speed limit of this speed zone */
	bool bIsVehicleExceedingSpeedLimit = false;

	/** If the player's vehicle is currently in this speed zone */
	bool bIsVehicleInSpeedZone = false;

public:
	ASpeedZone();

	virtual void BeginPlay() override;
	
	/** Speed limit in cm/s */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Speed Zone|Properties" )
	float SpeedLimit = 1388.89f;

	virtual void Tick( float DeltaSeconds ) override;
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
	virtual void NotifyActorEndOverlap( AActor* OtherActor ) override;
};
