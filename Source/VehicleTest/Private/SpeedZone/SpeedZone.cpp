// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleTest/Public/Speedzone/SpeedZone.h"

#include "VehicleTest/VehicleTestGameMode.h"

ASpeedZone::ASpeedZone()
{
	
}

void ASpeedZone::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap( OtherActor );

	// make sure that other actor is actually the player
	if ( const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController() )
		if ( OtherActor != PlayerController->GetPawn() )
			return;

	if ( AVehicleTestGameMode* GameMode = Cast< AVehicleTestGameMode >( GetWorld()->GetAuthGameMode() ) )
		GameMode->SetCurrentSpeedZone( this );
}
