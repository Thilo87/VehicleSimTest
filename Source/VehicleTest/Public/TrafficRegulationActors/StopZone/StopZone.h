// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "StopZone.generated.h"

class AVehicleTestPlayerController;

/**
 * Actor for a stop zone. Once entered, the player's vehicle has to stop for a while.
 */
UCLASS( Category = "Stop Zone" )
class VEHICLETEST_API AStopZone : public ATriggerBox
{
	GENERATED_BODY()

	/** Pointer to the player controller */
	TWeakObjectPtr< AVehicleTestPlayerController > PlayerController;

	/** How long the player's vehicle was at zero speed in the stop zone */
	float DurationVehicleInStopZoneAtZeroSpeed = 0.f;

	/** If the player's vehicle is currently in this stop zone */
	bool bIsVehicleInStopZone = false;

	/** If the player's vehicle stopped long enough while it was in the stop zone */
	bool bStoppedLongEnough = false;

public:
	AStopZone();

	virtual void BeginPlay() override;

	/** Duration the player's vehicle has to stop in the stop zone in seconds */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stop Zone|Properties" )
	float MinStopDuration = 1.f;
	
	virtual void Tick( float DeltaSeconds ) override;
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
	virtual void NotifyActorEndOverlap( AActor* OtherActor ) override;
};
