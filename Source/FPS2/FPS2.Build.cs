// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPS2 : ModuleRules
{
	public FPS2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
