// Copyright June Rhodes 2024. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public class RedpointDiscordGameSDKRuntime : ModuleRules
{
	public RedpointDiscordGameSDKRuntime(ReadOnlyTargetRules Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ShortName = "RDGSR";
		if (Environment.GetEnvironmentVariable("REDPOINT_EOS_STRICT_BUILD") == "1")
		{
			CppStandard = CppStandardVersion.Cpp17;
			bUseUnity = false;
		}

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"Projects",
				"RedpointDiscordGameSDK",
			}
		);

		OnlineSubsystemRedpointEOS.ApplyEngineVersionDefinesToModule(this);

		/* PRECOMPILED REMOVE BEGIN */
		if (!bUsePrecompiled)
		{
			// This can't use OnlineSubsystemRedpointEOSConfig.GetBool because the environment variable comes
			// from the standard build scripts.
			if (Environment.GetEnvironmentVariable("BUILDING_FOR_REDISTRIBUTION") == "true")
			{
				bTreatAsEngineModule = true;
				bPrecompile = true;

				// Force the module to be treated as an engine module for UHT, to ensure UPROPERTY compliance.
#if UE_5_0_OR_LATER
				object ContextObj = this.GetType().GetProperty("Context", BindingFlags.Instance | BindingFlags.NonPublic).GetValue(this);
#else
                object ContextObj = this.GetType().GetField("Context", BindingFlags.Instance | BindingFlags.NonPublic).GetValue(this);
#endif
				ContextObj.GetType().GetField("bClassifyAsGameModuleForUHT", BindingFlags.Instance | BindingFlags.Public).SetValue(ContextObj, false);
			}
		}
		/* PRECOMPILED REMOVE END */
	}
}