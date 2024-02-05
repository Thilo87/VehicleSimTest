// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

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
