// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UE5VoxelTerrain : ModuleRules
{
	public UE5VoxelTerrain(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
