// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "TrafficRegulationActors/TrafficLight/TrafficLight.h"


float ATrafficLight::GetCurrentPhaseDuration() const
{
	return PhaseDurations[ static_cast< uint8 >( CurrentPhase ) ];
}

ETrafficLightPhase ATrafficLight::GetNextPhase() const
{
	return static_cast< ETrafficLightPhase >( ( static_cast< int >( CurrentPhase ) + 1 ) % 4 );
}

ETrafficLightPhase ATrafficLight::GetPreviousPhase() const
{
	return static_cast< ETrafficLightPhase >( ( static_cast< int >( CurrentPhase ) - 1 ) % 4 );
}

void ATrafficLight::OnPhaseTimerTriggered()
{
	CurrentPhase = GetNextPhase();

	// clear the current timer, set the timer again with the duration of the next phase
	GetWorld()->GetTimerManager().ClearTimer( PhaseTimer );
	GetWorld()->GetTimerManager().SetTimer(
		PhaseTimer,
		this,
		&ATrafficLight::OnPhaseTimerTriggered,
		GetCurrentPhaseDuration()
	);

	UpdateCollisionAndDesign();
}

void ATrafficLight::UpdateCollisionAndDesign()
{
	// enable or disable collision so that vehicles stop at red or amber phases
	if ( CurrentPhase == ETrafficLightPhase::Green || CurrentPhase == ETrafficLightPhase::RedAmber )
		TrafficLightZone->SetCollisionProfileName( "NoCollision" );
	else
		TrafficLightZone->SetCollisionProfileName( OBSTACLE_COLLISION_CHANNEL_NAME );
		
	OnTrafficLightPhaseChanged( CurrentPhase );
}

ATrafficLight::ATrafficLight()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMesh = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "Static Mesh" ) );
	RootComponent = StaticMesh;
	
	TrafficLightZone = CreateDefaultSubobject< UBoxComponent >( TEXT( "Traffic Light Zone" ) );
	TrafficLightZone->SetupAttachment( RootComponent );

	// set default collision profile
	TrafficLightZone->SetCollisionProfileName( OBSTACLE_COLLISION_CHANNEL_NAME );
}

void ATrafficLight::BeginPlay()
{
	PhaseDurations = { RedDuration, RedAmberDuration, GreenDuration, AmberDuration };
	CurrentPhase = StartingPhase;

	if ( bDelayFirstPhase )
	{
		GetWorld()->GetTimerManager().SetTimer(
			PhaseTimer,
			this,
			&ATrafficLight::OnPhaseTimerTriggered,
			FirstDelay
		);

		UpdateCollisionAndDesign();
		return;
	}

	// in OnPhaseTimerTriggered we proceed to the next phase, so to start at the current phase we need
	// first rewind the current phase to the previous one
	CurrentPhase = GetPreviousPhase();
	OnPhaseTimerTriggered();

	Super::BeginPlay();
}

ETrafficLightPhase ATrafficLight::GetCurrentPhase() const
{
	return CurrentPhase;
}
