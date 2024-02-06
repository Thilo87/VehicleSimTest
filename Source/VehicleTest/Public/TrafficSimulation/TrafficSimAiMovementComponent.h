// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChaosVehicleMovementComponent.h"
#include "TrafficSimPath.h"
#include "Components/ActorComponent.h"
#include "TrafficSimAiMovementComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( TrafficSimAiMovementComponentLog, Log, All );

/*
 * Component that controls the movement of an AI car along a path
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VEHICLETEST_API UTrafficSimAiMovementComponent : public UActorComponent
{
	GENERATED_BODY()

	/** Path the AI pawn is currently following */
	UPROPERTY()
	ATrafficSimPath* CurrentPath = nullptr;

	/** Destination on the current path the vehicle is moving towards */
	FVector CurrentDestination;
	void UpdateCurrentDestination();

	/** Current steering of the vehicle */
	float CurrentSteering;
	
	/** Updates the steering according to the destination on the path */
	void UpdateSteering();

	/** Gets the end location of the "fishing rod" */
	FVector GetFishingRodEndLocation() const;

	// TODO: don't consider Z-coordinate?
	/** Find the nearest location on a path to the owning actor */
	bool FindNearestPathAndLocation( ATrafficSimPath*& Path, FVector& WorldLocationOnPath ) const;

	/** Move the owning vehicle to the nearest location on a path */
	bool TeleportVehicleToNearestPathAndLocation();
	
	/** Reference to the vehicle movement component of the owning vehicle */
	TObjectPtr< UChaosVehicleMovementComponent > ChaosVehicleMovement;
	
public:
	UTrafficSimAiMovementComponent();
	
	/** The "fishing rod" is a line that begins at the actors location and has this length */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float FishingRodLength = 200.f;

	/** Minimum and maximum steering to follow a path in degrees */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FVector2D MinMaxSteeringDeg = FVector2D( -90.f, 90.f );

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent( float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction ) override;
};
