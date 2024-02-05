// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
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

	/** Helper for easier access to the durations of the phases - see UPROPERTY phase variables */
	TArray< float > PhaseDurations = { 10.f, 2.f, 10.f, 2.f };
	float GetCurrentPhaseDuration() const;
	ETrafficLightPhase GetNextPhase() const;
	ETrafficLightPhase GetPreviousPhase() const;
	
	/** Turns the traffic light off and on */
	void Restart();
	
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
	float RedDuration = 5.f;

	/** Red-amber phase duration */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float RedAmberDuration = 2.f;

	/** Green phase duration */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float GreenDuration = 5.f;

	/** Amber phase duration */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	float AmberDuration = 2.f;

	/** The phase the traffic light starts with */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light|Phases" )
	ETrafficLightPhase StartingPhase = ETrafficLightPhase::Red;

	
	/** Start the traffic light in BeginPlay()? */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Traffic Light" )
	bool bAutoStart = true;
	

	/** Get current phase of the traffic light */
	UFUNCTION( BlueprintPure )
	ETrafficLightPhase GetCurrentPhase() const;

	/** Set the phase durations */
	UFUNCTION( BlueprintCallable )
	void SetPhaseDurations( float NewRedDuration, float NewRedAmberDuration, float NewGreenDuration, float NewAmberDuration );

	
	/** Turns the traffic light on */
	UFUNCTION( BlueprintCallable )
	void TurnOn();

	/** Turns the traffic light off */
	UFUNCTION( BlueprintCallable )
	void TurnOff();

	
	/** If the traffic light is turned on */
	UFUNCTION( BlueprintPure )
	bool IsRunning() const;


	/** Called when the traffic light phase has changed */
	UFUNCTION( BlueprintImplementableEvent )
	void OnTrafficLightPhaseChanged( ETrafficLightPhase NewTrafficLightPhase );
};
