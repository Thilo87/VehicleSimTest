// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrafficSimPath.h"
#include "Components/ActorComponent.h"
#include "TrafficSimAiMovementComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( TrafficSimAiMovementComponentLog, Log, All );

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class VEHICLETEST_API UTrafficSimAiMovementComponent : public UActorComponent
{
	GENERATED_BODY()

	/** Path the AI pawn is currently following */
	UPROPERTY()
	ATrafficSimPath* CurrentPath;

	/** Destination on the current path the vehicle is moving towards */
	FVector CurrentDestination;

	FVector GetFishingRodEndLocation() const;

	// TODO: don't consider Z-coordinate?
	/** Find the nearest location on a path to the owning actor */
	bool FindNearestPathAndLocation( ATrafficSimPath*& Path, FVector& WorldLocationOnPath ) const;

	/** Move the owning vehicle to the nearest location on a path */
	bool MoveVehicleToNearestPathAndLocation();

public:
	UTrafficSimAiMovementComponent();
	
	/** The "fishing rod" is a line that begins at the actors location and has this length */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float FishingRodLength = 200.f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent( float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction ) override;
};
