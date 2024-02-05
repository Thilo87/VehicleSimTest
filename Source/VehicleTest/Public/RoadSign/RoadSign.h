// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadSign.generated.h"

/*
 * Base class for the design of a road sign
 */
UCLASS( abstract )
class VEHICLETEST_API ARoadSign : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
	TObjectPtr< UStaticMeshComponent > StaticMesh;

public:
	ARoadSign();
};
