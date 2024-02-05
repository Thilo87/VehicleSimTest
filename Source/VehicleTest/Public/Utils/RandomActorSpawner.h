// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomActorSpawner.generated.h"

/*
 * Actor that randomly spawns actors at it's location
 */
UCLASS()
class VEHICLETEST_API ARandomActorSpawner : public AActor
{
	GENERATED_BODY()

	float TimeElapsedWithoutSpawnedActor = 0.f;
	int NumSpawnedActors = 0;
	
public:
	ARandomActorSpawner();

	/** Classes to select the actors to spawn from */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray< TSubclassOf< AActor > > ActorClasses;

	/** Number of actors to spawn per minute */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float AvgNumActorsToSpawnPerMinute = 10.f;

	/** Minimum time (seconds) between spawned actors */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	float MinTimeBetweenSpawnedActors = 5.f;

	virtual void Tick( float DeltaSeconds ) override;
};
