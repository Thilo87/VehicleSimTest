// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "TrafficSimulation/TrafficSimAiControlledCarKillVolume.h"

#include "Components/ShapeComponent.h"
#include "TrafficSimulation/AiControlledCar/TrafficSimAiControlledCar.h"

ATrafficSimAiControlledCarKillVolume::ATrafficSimAiControlledCarKillVolume()
{
	GetCollisionComponent()->SetCollisionProfileName( "OverlapAll" );
}

void ATrafficSimAiControlledCarKillVolume::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap( OtherActor );

	if ( Cast< ATrafficSimAiControlledCar >( OtherActor ) )
		OtherActor->Destroy();
}
