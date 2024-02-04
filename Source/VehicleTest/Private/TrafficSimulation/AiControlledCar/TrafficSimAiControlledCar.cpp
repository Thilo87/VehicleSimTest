// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficSimulation/AiControlledCar/TrafficSimAiControlledCar.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
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
	UpdateDistanceToCarAhead();
	UpdateShouldBreak();
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

void ATrafficSimAiControlledCar::UpdateDistanceToCarAhead()
{
	FHitResult HitResult;

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
		HitResult,
		true
		);
	
	SetDistanceToCarAhead( bWasHit ? HitResult.Distance : TNumericLimits< float >::Max() );
}

void ATrafficSimAiControlledCar::SetDistanceToCarAhead(float NewDistanceToCarAhead)
{
	DistanceToCarAhead = NewDistanceToCarAhead;
	AiController->GetBlackboardComponent()->SetValueAsFloat( BBTNameDistanceToCarAhead, DistanceToCarAhead );
}

void ATrafficSimAiControlledCar::UpdateShouldBreak()
{
	if ( DistanceToCarAhead <= EstimatedBrakingDistance || DistanceToCarAhead <= MinDistanceToCarAhead )
		SetShouldBreak( true );
	else
		SetShouldBreak( false );
}

void ATrafficSimAiControlledCar::SetShouldBreak(bool NewShouldBreak)
{
	bShouldBreak = NewShouldBreak;
	AiController->GetBlackboardComponent()->SetValueAsBool( BBTNameShouldBreak, bShouldBreak );
}


void ATrafficSimAiControlledCar::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );

	UpdateBlackboardVariables();
}
