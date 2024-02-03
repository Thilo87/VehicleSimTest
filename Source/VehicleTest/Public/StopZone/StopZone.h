// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "StopZone.generated.h"

class AVehicleTestPlayerController;

UCLASS()
class VEHICLETEST_API AStopZone : public ATriggerBox
{
	GENERATED_BODY()

	TWeakObjectPtr< AVehicleTestPlayerController > PlayerController;

public:
	AStopZone();
	
};
