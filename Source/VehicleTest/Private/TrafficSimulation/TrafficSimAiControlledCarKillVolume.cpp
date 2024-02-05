// Fill out your copyright notice in the Description page of Project Settings.


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
