// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "Components/BoxComponent.h"
#include "TrafficLight.generated.h"

/*
 * A traffic light actor
 */
UCLASS( Category = "Traffic Light" )
class VEHICLETEST_API ATrafficLight : public AActor
{
	GENERATED_BODY()

	/** Current light phase of the traffic light */
	ETrafficLightPhase CurrentPhase = ETrafficLightPhase::Green;

	/** Timer that triggers the next phase */
	FTimerHandle PhaseTimer;

	/** Called by the timer - starts the next phase */
	UFUNCTION()
	void OnPhaseTimerTriggered();

	/** Update the collision according to the phase (e.g. collision enabled in red phase) and call event to update design */
	void UpdateCollisionAndDesign();

	/** Helper for easier access to the durations of the phases - see UPROPERTY phase variables */
	TArray< float > PhaseDurations = { 10.f, 2.f, 10.f, 2.f };
	float GetCurrentPhaseDuration() const;
	ETrafficLightPhase GetNextPhase() const;
	ETrafficLightPhase GetPreviousPhase() const;
	
	/** Static mesh of the traffic light */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ), Category = "Traffic Light" )
	TObjectPtr< UStaticMeshComponent > StaticMesh;

	/** Zone where the first cars should stop if the traffic light is red */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ), Category = "Traffic Light" )
	TObjectPtr< UBoxComponent > TrafficLightZone;

public:
	ATrafficLight();
	virtual void BeginPlay() override;

	
	/** Red phase duration */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float RedDuration = 14.f;

	/** Red-amber phase duration */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float RedAmberDuration = 2.f;

	/** Green phase duration */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float GreenDuration = 6.f;

	/** Amber phase duration */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float AmberDuration = 1.f;

	/** If we should delay the first phase - usually one side of the traffic lights should delay the first phase, the other one not */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	bool bDelayFirstPhase = false;

	/** Duration of the first delay */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float FirstDelay = 3.f;

	/** The phase the traffic light starts with */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	ETrafficLightPhase StartingPhase = ETrafficLightPhase::Red;
	

	/** Get current phase of the traffic light */
	UFUNCTION( BlueprintPure )
	ETrafficLightPhase GetCurrentPhase() const;

	
	/** Called when the traffic light phase has changed */
	UFUNCTION( BlueprintImplementableEvent )
	void OnTrafficLightPhaseChanged( ETrafficLightPhase NewTrafficLightPhase );
};
