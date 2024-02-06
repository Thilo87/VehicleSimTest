// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "TrafficSimulation/TrafficSimAIMovementComponent.h"
#include "WheeledVehiclePawn.h"
#include "TrafficRegulationActors/Speedzone/SpeedZone.h"
#include "TrafficSimulation/TrafficSimAIController.h"
#include "UObject/Object.h"
#include "TrafficSimAiControlledCar.generated.h"

/**
 * More simple vehicle controlled, should be controlled by the AI
 */
UCLASS()
class VEHICLETEST_API ATrafficSimAiControlledCar : public AWheeledVehiclePawn
{
	GENERATED_BODY()

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true") )
	TObjectPtr<UTrafficSimAiMovementComponent > AiMovementComponent;

	/** Cast pointer to the Chaos Vehicle movement component */
	TObjectPtr< UChaosWheeledVehicleMovementComponent > ChaosVehicleMovement;

	TObjectPtr< ATrafficSimAIController > AiController;


	/** Updates all blackboard variables (calls the update-methods below). The order in which those are executed is crucial. */
	void UpdateBlackboardVariables();
	
	/** Calculates an estimated breaking distance */
	FORCEINLINE void UpdateEstimatedBrakingDistance();
	FORCEINLINE void SetEstimatedBrakingDistance( float NewEstimatedBrakingDistance );
	float EstimatedBrakingDistance;

	/** Checks if there is any obstacle ahead (wall, vehicle, red traffic light). Saves the result. */
	FHitResult ObstacleAheadHitResult;
	FORCEINLINE void UpdateDistanceToObstacleAhead();
	FORCEINLINE void SetDistanceToObstacleAhead( float NewDistanceToObstacleAhead );
	float DistanceToObstacleAhead = TNumericLimits< float >::Max();

	/** Calculates the distance to a location where the vehicle should stop */
	FORCEINLINE void UpdateDistanceToStopPoint();
	FORCEINLINE void SetDistanceToStopPoint( float NewDistanceToStopPoint );
	float DistanceToStopPoint = TNumericLimits< float >::Max();

	/** Decides if the vehicle should break */
	FORCEINLINE void UpdateShouldBreak();
	FORCEINLINE void SetShouldBreak( bool NewShouldBreak );
	bool bShouldBreak = false;

	/** Calculates a suggested breaking strength for the vehicle if it should break (bShouldBreak == true) */
	FORCEINLINE void UpdateSuggestedBreakStrength();
	FORCEINLINE void SetSuggestedBreakStrength( float NewSuggestedBreakStrength );
	float SuggestedBreakStrength = 0.f;

	
	/*
	 * Speed limit
	 */

	float CurrentSpeedLimit = 1388.89f;

	/** Updates if the vehicle is above the speed limit of the speed zone it's currently driving in */
	FORCEINLINE void UpdateAboveSpeedLimit();
	FORCEINLINE void SetAboveSpeedLimit( bool NewAboveSpeedLimit );
	bool bAboveSpeedLimit = false;

	/** Updates if the vehicle is below the speed limit of the speed zone it's currently driving in */
	FORCEINLINE void UpdateBelowSpeedLimit();
	FORCEINLINE void SetBelowSpeedLimit( bool NewBelowSpeedLimit );
	bool bBelowSpeedLimit = false;

public:
	ATrafficSimAiControlledCar();

	virtual void BeginPlay() override;
	
	/*
	 * Blackboard variable names
	 */

	/** Blackboard variable containing the estimated braking distance in cm */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameEstimatedBrakingDistance = "EstimatedBrakingDistance";

	/** Blackboard variable containing the distance to the next car following the forward vector of the vehicle */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameDistanceToObstacleAhead = "DistanceToObstacleAhead";

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameDistanceToStopPoint = "DistanceToStopPoint";

	/** Blackboard variable saying if the car should break (if the estimated braking distance is almost the distance to the car ahead) */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameShouldBreak = "bShouldBreak";

	/** A suggestion for the AI which break strength it should use if bShouldBreak is true */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameSuggestedBrakeStrength = "SuggestedBreakStrength";

	/** If the vehicle is above the current speed limit */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameAboveSpeedLimit = "bAboveSpeedLimit";

	/** If the vehicle is below the current speed limit */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameBelowSpeedLimit = "bBelowSpeedLimit";

	
	/** Minimum distance the vehicle should maintain to the car ahead */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MinDistanceToVehicle = 1000.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MinDistanceToTrafficLight = 1000.f;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MinDistanceToStopLine = 100.f;

	/** Collision channel for vehicles */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TEnumAsByte< ETraceTypeQuery > VehicleCollisionChannel = UEngineTypes::ConvertToTraceType( ECC_GameTraceChannel1 );

	/** The distance in the direction of the forward vector of the vehicle in which we look for other vehicles */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float VehicleCollisionTraceDistance = 10000.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FVector VehicleCollisionBoxTraceHalfSize = FVector( 0.f, 50.f, 1000.f );

	/** Default speed limit of the vehicle if it's not in any speed zone */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float DefaultSpeedLimit = 1388.89f; // 50 km/h
	
	void OnEnteredSpeedZone( ASpeedZone* SpeedZone );
	void OnLeftSpeedZone();
	
	FORCEINLINE const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }

	virtual void Tick( float DeltaSeconds ) override;
};
