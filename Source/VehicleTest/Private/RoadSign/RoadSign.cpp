// Fill out your copyright notice in the Description page of Project Settings.


#include "RoadSign/RoadSign.h"


ARoadSign::ARoadSign()
{
	StaticMesh = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "Static Mesh" ) );
	RootComponent = StaticMesh;
}
