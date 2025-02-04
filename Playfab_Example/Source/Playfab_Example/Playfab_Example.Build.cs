// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Playfab_Example : ModuleRules
{
	public Playfab_Example(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
				"PlayFabCommon", "PlayFabCpp", "HTTP", "Json", "JsonUtilities", 
				"UMG" 
			}
		);
		PrivateDependencyModuleNames.AddRange(new string[] {});
	}
}
