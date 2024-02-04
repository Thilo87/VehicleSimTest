// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class VehicleTest : ModuleRules
{
	public VehicleTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosVehicles", "PhysicsCore", "AIModule" });
	}
}
