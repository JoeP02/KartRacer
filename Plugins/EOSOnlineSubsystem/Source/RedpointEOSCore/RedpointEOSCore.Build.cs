// Copyright June Rhodes 2024. All Rights Reserved.

using System;
using UnrealBuildTool;

public class RedpointEOSCore : ModuleRules
{
	public RedpointEOSCore(ReadOnlyTargetRules Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ShortName = "REC";
		if (Environment.GetEnvironmentVariable("REDPOINT_EOS_STRICT_BUILD") == "1")
		{
			CppStandard = CppStandardVersion.Cpp17;
			bUseUnity = false;
		}

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"CoreOnline",
			"Engine",
			"RedpointEOSSDK",
			"RedpointEOSAPI",
			"RedpointEOSConfig",
		});

		if (Target.Type == TargetType.Server)
		{
			PrivateDefinitions.Add("REDPOINT_EOS_IS_DEDICATED_SERVER=1");
		}
		else
		{
			PrivateDefinitions.Add("REDPOINT_EOS_IS_DEDICATED_SERVER=0");
		}
	}
}