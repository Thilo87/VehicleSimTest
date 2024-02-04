// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "TrafficSimulation/TrafficSimAIMovementComponent.h"
#include "WheeledVehiclePawn.h"
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

public:
	ATrafficSimAiControlledCar();
	
	FORCEINLINE const TObjectPtr<UChaosWheeledVehicleMovementComponent>& GetChaosVehicleMovement() const { return ChaosVehicleMovement; }
};
