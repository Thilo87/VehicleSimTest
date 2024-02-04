// Fill out your copyright notice in the Description page of Project Settings.


#include "TrafficSimulation/TrafficSimAiMovementComponent.h"

#include "EngineUtils.h"

DEFINE_LOG_CATEGORY( TrafficSimAiMovementComponentLog );

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

bool UTrafficSimAiMovementComponent::MoveVehicleToNearestPathAndLocation()
{
	FVector Location;
	if ( !FindNearestPathAndLocation( CurrentPath, Location ) )
		return false;

	GetOwner()->SetActorLocation( Location, false, nullptr, ETeleportType::TeleportPhysics );
	return true;
}

FVector UTrafficSimAiMovementComponent::GetFishingRodEndLocation() const
{
	return GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * FishingRodLength;
}

UTrafficSimAiMovementComponent::UTrafficSimAiMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTrafficSimAiMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	if ( !MoveVehicleToNearestPathAndLocation() )
		UE_LOG( TrafficSimAiMovementComponentLog, Warning, TEXT( "Failed to find starting point for AI controlled vehicle" ) )
}


// Called every frame
void UTrafficSimAiMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

