// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "StopZone.generated.h"

class AVehicleTestPlayerController;

/**
 * Actor for a stop zone. Once entered, the player's vehicle has to stop for a while.
 */
UCLASS( Category = "Stop Zone" )
class VEHICLETEST_API AStopZone : public AActor
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

	/** Root scene component helper */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ), Category = "Stop Zone" )
	TObjectPtr< USceneComponent > RootSceneComponent;

	/** Zone where the player or AI vehicles should stop */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ), Category = "Stop Zone" )
	TObjectPtr< UBoxComponent > StandingZone;

	/** Zone where the stop line is. Is used for AI to be able to see the stop line. */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ), Category = "Stop Zone" )
	TObjectPtr< UBoxComponent > StopLineZone;

	UFUNCTION()
	void OnStandingZoneBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnStandingZoneEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

public:
	AStopZone();

	virtual void BeginPlay() override;

	/** Duration the player's vehicle has to stop in the stop zone in seconds */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Stop Zone|Properties" )
	float MinStopDuration = 1.f;
	
	virtual void Tick( float DeltaSeconds ) override;
};
