// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Drone_simulator : ModuleRules
{
	public Drone_simulator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"UMG",
			"UnrealEd", 
			"AssetTools",
			"LidarPointCloudRuntime"
        });

		PrivateDependencyModuleNames.AddRange(new string[] { });

        // Dodanie warunku, aby dodaæ bibliotekê Comdlg32.lib dla platformy Windows
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicAdditionalLibraries.Add("Comdlg32.lib");
        }
        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
