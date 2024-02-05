// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "TrafficSimulation/TrafficSimAiMovementComponent.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(TrafficSimAiMovementComponentLog);

bool UTrafficSimAiMovementComponent::FindNearestPathAndLocation(ATrafficSimPath*& Path, FVector& WorldLocationOnPath) const
{
	Path = nullptr;
	WorldLocationOnPath = FVector::Zero();
	
	float MinDistanceSquared = 0.f;
	
	for ( TActorIterator< ATrafficSimPath > PathIt( GetWorld(), ATrafficSimPath::StaticClass() ); PathIt; ++PathIt )
	{
		const USplineComponent* Spline = ( *PathIt )->Spline;
		const float InputKey = Spline->FindInputKeyClosestToWorldLocation( GetOwner()->GetActorLocation() );
		const FVector Location = Spline->GetLocationAtSplineInputKey( InputKey, ESplineCoordinateSpace::World );
		const float DistanceToOwnerSquared = FVector::DistSquared( Location, GetOwner()->GetActorLocation() );

		if ( DistanceToOwnerSquared < MinDistanceSquared || !Path )
		{
			MinDistanceSquared = DistanceToOwnerSquared;
			Path = *PathIt;
			WorldLocationOnPath = Location;
		}
	}

	return Path != nullptr;
}

bool UTrafficSimAiMovementComponent::TeleportVehicleToNearestPathAndLocation()
{
	FVector Location;
	if ( !FindNearestPathAndLocation( CurrentPath, Location ) )
		return false;

	GetOwner()->SetActorLocation( Location, false, nullptr, ETeleportType::TeleportPhysics );
	return true;
}

void UTrafficSimAiMovementComponent::UpdateCurrentDestination()
{
	if ( !IsValid( CurrentPath ) )
		return;

	const USplineComponent* Spline = CurrentPath->Spline;
	const float InputKey = Spline->FindInputKeyClosestToWorldLocation( GetFishingRodEndLocation() );
	CurrentDestination = Spline->GetLocationAtSplineInputKey( InputKey, ESplineCoordinateSpace::World );
	
}

FVector UTrafficSimAiMovementComponent::GetFishingRodEndLocation() const
{
	return GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * FishingRodLength;
}

void UTrafficSimAiMovementComponent::UpdateSteering()
{
	if ( !ChaosVehicleMovement )
		return;

	const FRotator& TargetRotation = UKismetMathLibrary::FindLookAtRotation( GetOwner()->GetActorLocation(), CurrentDestination );
	const FRotator& DeltaRotation = UKismetMathLibrary::NormalizedDeltaRotator( GetOwner()->GetActorRotation(), TargetRotation );
	
	CurrentSteering = FMath::GetMappedRangeValueClamped< float >( 
	TRange< float >( MinMaxSteeringDeg.X, MinMaxSteeringDeg.Y ),
	TRange< float >( -1.f, 1.f ),
			-DeltaRotation.Yaw );

	ChaosVehicleMovement->SetSteeringInput( CurrentSteering );
}

UTrafficSimAiMovementComponent::UTrafficSimAiMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTrafficSimAiMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if ( !TeleportVehicleToNearestPathAndLocation() )
		UE_LOG( TrafficSimAiMovementComponentLog, Error, TEXT( "Failed to find starting point for AI controlled vehicle" ) )

	ChaosVehicleMovement = GetOwner()->GetComponentByClass< UChaosVehicleMovementComponent >();
	if ( !ChaosVehicleMovement )
		UE_LOG( TrafficSimAiMovementComponentLog, Error, TEXT( "Owner has no chaos vehicle movement component" ) )
}


// Called every frame
void UTrafficSimAiMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	UpdateCurrentDestination();
	UpdateSteering();
}

