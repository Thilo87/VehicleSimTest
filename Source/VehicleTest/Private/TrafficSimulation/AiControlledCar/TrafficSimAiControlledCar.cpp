// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficSimulation/AiControlledCar/TrafficSimAiControlledCar.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TrafficRegulationActors/TrafficLight/TrafficLight.h"
#include "TrafficSimulation/TrafficSimAIController.h"

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
	
	UpdateEstimatedBrakingDistance();
	UpdateDistanceToObstacleAhead();
	UpdateShouldBreak();
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
		VehicleCollisionChannel,
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

void ATrafficSimAiControlledCar::UpdateShouldBreak()
{
	if ( !IsValid( ObstacleAheadHitResult.GetActor() ) )
	{
		SetShouldBreak( false );
		return;
	}

	// if ( const ATrafficLight* TrafficLight = Cast< ATrafficLight >( ObstacleAheadHitResult.GetActor() ) )
	// {
	// 	if ( EstimatedBrakingDistance <= ( TrafficLight->GetActorLocation() - GetActorLocation() ).Length() )
	// 		SetShouldBreak( true );
	// 	else
	// 		SetShouldBreak( false );
	// 	
	// 	return;
	// }
	
	if ( DistanceToObstacleAhead <= EstimatedBrakingDistance
		|| DistanceToObstacleAhead <= MinDistanceToObstacleAhead )
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


void ATrafficSimAiControlledCar::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );

	UpdateBlackboardVariables();
}
