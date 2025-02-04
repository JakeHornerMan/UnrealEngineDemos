using UnrealBuildTool;

public class Authentication : ModuleRules 
{
    public Authentication(ReadOnlyTargetRules Target) : base(Target) 
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG", "Playfab_Example", "PlayFabCommon", "PlayFabCpp" });
    }
}