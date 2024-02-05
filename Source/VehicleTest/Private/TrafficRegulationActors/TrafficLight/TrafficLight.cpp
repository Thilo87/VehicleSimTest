// Fill out your copyright notice in the Description page of Project Settings.


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

bool ATrafficLight::IsRunning() const
{
	return GetWorld()->GetTimerManager().IsTimerActive( PhaseTimer );
}

void ATrafficLight::OnPhaseTimerTriggered()
{
	CurrentPhase = GetNextPhase();

	GetWorld()->GetTimerManager().ClearTimer( PhaseTimer );
	GetWorld()->GetTimerManager().SetTimer(
		PhaseTimer,
		this,
		&ATrafficLight::OnPhaseTimerTriggered,
		GetCurrentPhaseDuration()
	);

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

	if ( bAutoStart )
		TurnOn();

	Super::BeginPlay();
}

ETrafficLightPhase ATrafficLight::GetCurrentPhase()
{
	return CurrentPhase;
}

void ATrafficLight::TurnOn()
{
	if ( IsRunning() )
		return;

	CurrentPhase = GetPreviousPhase();
	OnPhaseTimerTriggered();
}

void ATrafficLight::TurnOff()
{
	if ( !IsRunning() )
		return;

	GetWorld()->GetTimerManager().ClearTimer( PhaseTimer );
}

void ATrafficLight::Restart()
{
	if ( IsRunning() )
	{
		TurnOff();
		TurnOn();
	}
}

void ATrafficLight::SetPhaseDurations(float NewRedDuration, float NewRedAmberDuration, float NewGreenDuration,
                                      float NewAmberDuration)
{
	PhaseDurations = { NewRedDuration, NewRedAmberDuration, NewGreenDuration, NewAmberDuration };
	Restart();
}
