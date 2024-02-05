// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "Utils/RandomActorSpawner.h"


ARandomActorSpawner::ARandomActorSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ARandomActorSpawner::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );
	
	TimeElapsedWithoutSpawnedActor += DeltaSeconds;

	if ( NumSpawnedActors != 0 &&
		( TimeElapsedWithoutSpawnedActor < MinTimeBetweenSpawnedActors
		|| 	ActorClasses.IsEmpty() ) )
		return;

	const float SpawnProbability = DeltaSeconds * ( AvgNumActorsToSpawnPerMinute / 60.f );
	const float RandFloat01 = FMath::RandRange( 0.f, 1.f );
	
	if ( RandFloat01 <= SpawnProbability )
	{
		TimeElapsedWithoutSpawnedActor = 0.f;
		const int RandIndex = FMath::RandRange( 0, ActorClasses.Num() - 1 );
		
		GetWorld()->SpawnActor< AActor >(
			ActorClasses[ RandIndex ],
			GetActorLocation(),
			GetActorRotation()
			);

		++NumSpawnedActors;
	}
}

