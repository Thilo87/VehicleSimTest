// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "TrafficSimulation/AiControlledCar/TrafficSimAiControlledCar.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Pawns/VehicleTestPawn.h"
#include "TrafficRegulationActors/StopZone/StopZone.h"
#include "TrafficRegulationActors/TrafficLight/TrafficLight.h"
#include "TrafficSimulation/TrafficSimAIController.h"

void ATrafficSimAiControlledCar::SetIsInStopZone(bool NewIsInStopZone)
{
	bIsInStopZone = NewIsInStopZone;
	AiController->GetBlackboardComponent()->SetValueAsBool( BBTNameIsInStopZone, bIsInStopZone );
}

ATrafficSimAiControlledCar::ATrafficSimAiControlledCar()
{
	GetMesh()->SetSimulatePhysics( true );
	GetMesh()->SetCollisionProfileName( FName( "Vehicle" ) );
	
	ChaosVehicleMovement = CastChecked< UChaosWheeledVehicleMovementComponent >( GetVehicleMovement() );
	AiMovementComponent = CreateDefaultSubobject< UTrafficSimAiMovementComponent >( TEXT( "Ai Movement" ) );
}

void ATrafficSimAiControlledCar::BeginPlay()
{
	Super::BeginPlay();

	AiController = Cast< ATrafficSimAIController >( GetController() );
}

void ATrafficSimAiControlledCar::UpdateBlackboardVariables()
{
	if ( !AiController || !AiController->GetBlackboardComponent() )
		return;

	// the order in which those methods are called is crucial!
	
	UpdateDistanceToObstacleAhead();

	UpdateEstimatedBrakingDistance();
	UpdateDistanceToStopPoint();
	UpdateShouldBreak();
	
	UpdateSuggestedBreakStrength();
	
	UpdateAboveSpeedLimit();
	UpdateBelowSpeedLimit();
}

void ATrafficSimAiControlledCar::UpdateEstimatedBrakingDistance()
{
	const float ForwardSpeed = FMath::Abs( ChaosVehicleMovement->GetForwardSpeed() );
	SetEstimatedBrakingDistance( ForwardSpeed * ForwardSpeed * 0.001296f );
}

void ATrafficSimAiControlledCar::SetEstimatedBrakingDistance(float NewEstimatedBrakingDistance)
{
	EstimatedBrakingDistance = NewEstimatedBrakingDistance;
	AiController->GetBlackboardComponent()->SetValueAsFloat( BBTNameEstimatedBrakingDistance, EstimatedBrakingDistance );
}

void ATrafficSimAiControlledCar::UpdateDistanceToObstacleAhead()
{
	const bool bWasHit = UKismetSystemLibrary::BoxTraceSingle(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * VehicleCollisionTraceDistance,
		VehicleCollisionBoxTraceHalfSize,
		FRotator( 0.f, 0.f, 0.f ),
		VehicleCollisionChannel, // TODO: change to obstacle collision channel
		false,
		TArray< AActor* >( { this } ),
		EDrawDebugTrace::None,
		ObstacleAheadHitResult,
		true
		);
	
	SetDistanceToObstacleAhead( bWasHit ? ObstacleAheadHitResult.Distance : TNumericLimits< float >::Max() );
}

void ATrafficSimAiControlledCar::SetDistanceToObstacleAhead(float NewDistanceToObstacleAhead)
{
	DistanceToObstacleAhead = NewDistanceToObstacleAhead;
	AiController->GetBlackboardComponent()->SetValueAsFloat( BBTNameDistanceToObstacleAhead, DistanceToObstacleAhead );
}

void ATrafficSimAiControlledCar::UpdateDistanceToStopPoint()
{
	if ( !IsValid( ObstacleAheadHitResult.GetActor() ) )
	{
		SetDistanceToStopPoint( TNumericLimits< float >::Max() );
		return;
	}

	const AActor* ActorAhead = ObstacleAheadHitResult.GetActor();
	
	float MinDistance = 0.f;
	if ( Cast< ATrafficLight >( ActorAhead ) )
		MinDistance = MinDistanceToTrafficLight;
	else if ( Cast< AStopZone >( ActorAhead ) )
		MinDistance = MinDistanceToStopLine;
	else if ( Cast< ATrafficSimAiControlledCar >( ActorAhead ) || Cast< AVehicleTestPawn >( ActorAhead ) )
		MinDistance = MinDistanceToVehicle;

	SetDistanceToStopPoint( FMath::Max( 0.f, DistanceToObstacleAhead - MinDistance ) );
}

void ATrafficSimAiControlledCar::SetDistanceToStopPoint(float NewDistanceToStopPoint)
{
	DistanceToStopPoint = NewDistanceToStopPoint;
	AiController->GetBlackboardComponent()->SetValueAsFloat( BBTNameDistanceToStopPoint, DistanceToStopPoint );
}

void ATrafficSimAiControlledCar::UpdateShouldBreak()
{
	if ( !IsValid( ObstacleAheadHitResult.GetActor() ) )
	{
		SetShouldBreak( false );
		return;
	}
	
	if ( DistanceToStopPoint <= EstimatedBrakingDistance )
	{
		SetShouldBreak( true );
		return;
	}

	SetShouldBreak( false );
}

void ATrafficSimAiControlledCar::SetShouldBreak(bool NewShouldBreak)
{
	bShouldBreak = NewShouldBreak;
	AiController->GetBlackboardComponent()->SetValueAsBool( BBTNameShouldBreak, bShouldBreak );
}

void ATrafficSimAiControlledCar::UpdateSuggestedBreakStrength()
{
	if ( !bShouldBreak )
	{
		SetSuggestedBreakStrength( 0.f );
		return;
	}
	
	SetSuggestedBreakStrength( FMath::Clamp( 0.f, 1.f, EstimatedBrakingDistance / DistanceToStopPoint ) );
}

void ATrafficSimAiControlledCar::SetSuggestedBreakStrength(float NewSuggestedBreakStrength)
{
	SuggestedBreakStrength = NewSuggestedBreakStrength;
	AiController->GetBlackboardComponent()->SetValueAsFloat( BBTNameSuggestedBrakeStrength, SuggestedBreakStrength );
}

void ATrafficSimAiControlledCar::UpdateAboveSpeedLimit()
{
	const float ForwardSpeed = FMath::Abs( ChaosVehicleMovement->GetForwardSpeed() );
	SetAboveSpeedLimit( ForwardSpeed > CurrentSpeedLimit );
}

void ATrafficSimAiControlledCar::SetAboveSpeedLimit( bool NewAboveSpeedLimit )
{
	bAboveSpeedLimit = NewAboveSpeedLimit;
	AiController->GetBlackboardComponent()->SetValueAsBool( BBTNameAboveSpeedLimit, bAboveSpeedLimit );
}

void ATrafficSimAiControlledCar::UpdateBelowSpeedLimit()
{
	const float ForwardSpeed = FMath::Abs( ChaosVehicleMovement->GetForwardSpeed() );
	SetBelowSpeedLimit( ForwardSpeed < CurrentSpeedLimit );
}

void ATrafficSimAiControlledCar::SetBelowSpeedLimit(bool NewBelowSpeedLimit)
{
	bBelowSpeedLimit = NewBelowSpeedLimit;
	AiController->GetBlackboardComponent()->SetValueAsBool( BBTNameBelowSpeedLimit, bBelowSpeedLimit );
}

void ATrafficSimAiControlledCar::OnEnteredSpeedZone(ASpeedZone* SpeedZone)
{
	CurrentSpeedLimit = SpeedZone->SpeedLimit;
}

void ATrafficSimAiControlledCar::OnLeftSpeedZone()
{
	CurrentSpeedLimit = DefaultSpeedLimit;
}

void ATrafficSimAiControlledCar::OnEnteredStopZone(AStopZone* StopZone)
{
	SetIsInStopZone( true );
}

void ATrafficSimAiControlledCar::OnLeftStopZone()
{
	SetIsInStopZone( false );
}


void ATrafficSimAiControlledCar::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );

	UpdateBlackboardVariables();
}
