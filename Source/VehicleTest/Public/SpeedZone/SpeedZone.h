// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "UObject/Object.h"
#include "SpeedZone.generated.h"

class AVehicleTestPlayerController;

/**
 * 
 */
UCLASS( Category = "Speed Zone" )
class VEHICLETEST_API ASpeedZone : public ATriggerBox
{
	GENERATED_BODY()
	
	TWeakObjectPtr< AVehicleTestPlayerController > PlayerController;
	bool bIsVehicleExceedingSpeedLimit = false;
	bool bIsVehicleInSpeedZone = false;

public:
	ASpeedZone();

	virtual void BeginPlay() override;
	
	/** Max allowed speed in cm/s */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Speed Zone|Properties" )
	float SpeedLimit = 1388.89f;

	virtual void Tick( float DeltaSeconds ) override;
	virtual void NotifyActorBeginOverlap( AActor* OtherActor ) override;
	virtual void NotifyActorEndOverlap( AActor* OtherActor ) override;
};
