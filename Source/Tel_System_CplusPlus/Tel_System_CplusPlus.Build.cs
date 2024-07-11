// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tel_System_CplusPlus : ModuleRules
{
	public Tel_System_CplusPlus(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput","UMG" });
	}
}
