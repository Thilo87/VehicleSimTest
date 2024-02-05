// Copyright (C) 2024 Thilo Noll. All Rights Reserved.

#include "RoadSign/RoadSign.h"


ARoadSign::ARoadSign()
{
	StaticMesh = CreateDefaultSubobject< UStaticMeshComponent >( TEXT( "Static Mesh" ) );
	RootComponent = StaticMesh;
}
