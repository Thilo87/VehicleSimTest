// Fill out your copyright notice in the Description page of Project Settings.

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
	UTrafficSimAiMovementComponent* AiMovementComponent;

	/** Cast pointer to the Chaos Vehicle movement component */
	TObjectPtr< UChaosWheeledVehicleMovementComponent > ChaosVehicleMovement;

	TObjectPtr< ATrafficSimAIController > AiController;


	
	void UpdateBlackboardVariables();
	
	/** Calculates an estimated breaking distance */
	void UpdateEstimatedBrakingDistance();
	void SetEstimatedBrakingDistance( float NewEstimatedBrakingDistance );
	float EstimatedBrakingDistance;
	
	void UpdateDistanceToObstacleAhead();
	void SetDistanceToObstacleAhead( float NewDistanceToObstacleAhead );
	float DistanceToObstacleAhead = TNumericLimits< float >::Max();

	void UpdateShouldBreak();
	void SetShouldBreak( bool NewShouldBreak );
	bool bShouldBreak = false;

	
	/*
	 * Speed limit
	 */

	float CurrentSpeedLimit = 1388.89f;
	
	void UpdateAboveSpeedLimit();
	void SetAboveSpeedLimit( bool NewAboveSpeedLimit );
	bool bAboveSpeedLimit = false;
	
	void UpdateBelowSpeedLimit();
	void SetBelowSpeedLimit( bool NewBelowSpeedLimit );
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

	/** Blackboard variable saying if the car should break (if the estimated braking distance is almost the distance to the car ahead) */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameShouldBreak = "bShouldBreak";

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameAboveSpeedLimit = "bAboveSpeedLimit";

	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	FName BBTNameBelowSpeedLimit = "bBelowSpeedLimit";

	
	/** Minimum distance the vehicle should maintain to the car ahead */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MinDistanceToCarAhead = 1000.f;

	/** Collision channel for vehicles */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	TEnumAsByte< ETraceTypeQuery > VehicleCollisionChannel = UEngineTypes::ConvertToTraceType( ECC_GameTraceChannel1 );

	/** The distance in the direction of the forward vector of the vehicle in which we look for other vehicles */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float VehicleCollisionTraceDistance = 10000.f;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FVector VehicleCollisionBoxTraceHalfSize = FVector( 0.f, 50.f, 1000.f );

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float DefaultSpeedLimit = 1388.89f;
	
	void OnEnteredSpeedZone( ASpeedZone* SpeedZone );
	void OnLeftSpeedZone();
	
	FORCEINLINE const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }

	virtual void Tick( float DeltaSeconds ) override;
};
