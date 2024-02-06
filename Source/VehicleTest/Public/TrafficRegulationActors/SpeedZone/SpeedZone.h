// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "UObject/Object.h"
#include "SpeedZone.generated.h"

class AVehicleTestPlayerController;

/**
 * Actor for a speed zone with a speed limit
 */
UCLASS( Category = "Speed Zone" )
class VEHICLETEST_API ASpeedZone : public AActor
{
	GENERATED_BODY()

	/** Pointer to the player controller */
	TWeakObjectPtr< AVehicleTestPlayerController > PlayerController;

	/** If the player's vehicle is currently exceeding the speed limit of this speed zone */
	bool bIsVehicleExceedingSpeedLimit = false;

	/** If the player's vehicle is currently in this speed zone */
	bool bIsVehicleInSpeedZone = false;

	/** Root scene component helper */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ), Category = "Speed Zone" )
	TObjectPtr< USceneComponent > RootSceneComponent;
	
	/** Zone where the vehicles are bound to the speed limit */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ), Category = "Speed Zone" )
	TObjectPtr< UBoxComponent > Zone;

	UFUNCTION()
	void OnSpeedZoneBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	UFUNCTION()
	void OnSpeedZoneEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex );

public:
	ASpeedZone();

	virtual void BeginPlay() override;
	
	/** Speed limit in cm/s */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Speed Zone|Properties" )
	float SpeedLimit = 1388.89f;

	virtual void Tick( float DeltaSeconds ) override;
};
