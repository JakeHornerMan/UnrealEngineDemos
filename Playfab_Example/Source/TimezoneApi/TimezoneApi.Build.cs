using UnrealBuildTool;

public class TimezoneApi : ModuleRules
{
    public TimezoneApi(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "UMG", "HTTP", "Json", "JsonUtilities", "UMG"  });
    }
}