// Copyright June Rhodes 2024. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public class OnlineSubsystemRedpointDiscord : ModuleRules
{
	public OnlineSubsystemRedpointDiscord(ReadOnlyTargetRules Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ShortName = "OSRD";
		if (Environment.GetEnvironmentVariable("REDPOINT_EOS_STRICT_BUILD") == "1")
		{
			CppStandard = CppStandardVersion.Cpp17;
			bUseUnity = false;
		}

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
		);

		OnlineSubsystemRedpointEOS.ApplyEngineVersionDefinesToModule(this);

		/* PRECOMPILED REMOVE BEGIN */
		if (!bUsePrecompiled)
		{
#if UE_5_1_OR_LATER
			PrivateDefinitions.Add("UE_5_1_OR_LATER=1");
#endif
#if UE_5_0_OR_LATER
			PrivateDefinitions.Add("UE_5_0_OR_LATER=1");
#endif
#if UE_4_27_OR_LATER
			PrivateDefinitions.Add("UE_4_27_OR_LATER=1");
#endif

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

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"CoreUObject",
					"Projects",
					"Json",
#if UE_5_0_OR_LATER
                    "HTTP",
#else
                    "Http",
#endif
                    "Engine",
					"OnlineSubsystemUtils",
					"OnlineSubsystem",
					"RedpointDiscordGameSDK",
					"RedpointDiscordGameSDKRuntime",
					"RedpointEOSInterfaces",

                    // Pull in WeakPtrHelpers.
                    "OnlineSubsystemRedpointEOS",
				}
			);
		}
		/* PRECOMPILED REMOVE END */
	}
}