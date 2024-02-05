// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Types.h"
#include "Components/BoxComponent.h"
#include "Components/ShapeComponent.h"
#include "TrafficLight.generated.h"

UCLASS()
class VEHICLETEST_API ATrafficLight : public AActor
{
	GENERATED_BODY()

	ETrafficLightPhase CurrentPhase = ETrafficLightPhase::Green;

	FTimerHandle PhaseTimer;
	
	TArray< float > PhaseDurations = { 10.f, 2.f, 10.f, 2.f };
	float GetCurrentPhaseDuration() const;
	ETrafficLightPhase GetNextPhase() const;
	ETrafficLightPhase GetPreviousPhase() const;

	UFUNCTION()
	void OnPhaseTimerTriggered();

	/** Static mesh of the traffic light */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
	TObjectPtr< UStaticMeshComponent > StaticMesh;

	/** Zone where the first cars should stop if the traffic light is red */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
	TObjectPtr< UBoxComponent > TrafficLightZone;

public:
	ATrafficLight();

	virtual void BeginPlay() override;

	/** Red phase duration */
	UPROPERTY( EditAnywhere )
	float RedDuration = 5.f;

	/** Red-amber phase duration */
	UPROPERTY( EditAnywhere )
	float RedAmberDuration = 2.f;

	/** Green phase duration */
	UPROPERTY( EditAnywhere )
	float GreenDuration = 5.f;

	/** Amber phase duration */
	UPROPERTY( EditAnywhere )
	float AmberDuration = 2.f;

	/** The phase the traffic light starts with */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	ETrafficLightPhase StartingPhase = ETrafficLightPhase::Red;

	/** Start the traffic light in BeginPlay()? */
	UPROPERTY( EditAnywhere, BlueprintReadOnly )
	bool bAutoStart = true;

	/** Get current phase of the traffic light */
	UFUNCTION( BlueprintPure )
	ETrafficLightPhase GetCurrentPhase();

	UFUNCTION( BlueprintCallable )
	void TurnOn();

	UFUNCTION( BlueprintCallable )
	void TurnOff();

	void Restart();

	UFUNCTION( BlueprintCallable )
	bool IsRunning() const;

	UFUNCTION( BlueprintCallable )
	void SetPhaseDurations( float NewRedDuration, float NewRedAmberDuration, float NewGreenDuration, float NewAmberDuration );
	
	UFUNCTION( BlueprintImplementableEvent )
	void OnTrafficLightPhaseChanged( ETrafficLightPhase NewTrafficLightPhase );
};
