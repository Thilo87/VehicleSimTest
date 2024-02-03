// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoadSign.generated.h"

UCLASS( abstract )
class VEHICLETEST_API ARoadSign : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, meta = ( AllowPrivateAccess = "true" ) )
	UStaticMeshComponent* StaticMesh;

public:
	ARoadSign();
};
