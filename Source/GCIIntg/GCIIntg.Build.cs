// Copyright (C) 2024 owoDra

using UnrealBuildTool;

public class GCIIntg : ModuleRules
{
	public GCIIntg(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                ModuleDirectory,
                ModuleDirectory + "/GCIIntg",
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "GCExt",
                "GIExt",
            }
        );

        SetupIrisSupport(Target);
    }
}
