// Copyright June Rhodes 2024. All Rights Reserved.

using UnrealBuildTool;
using System.IO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Diagnostics;

public class RedpointEOSVoiceChat : ModuleRules
{
	public RedpointEOSVoiceChat(ReadOnlyTargetRules Target) : base(Target)
	{
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ShortName = "REVC";
		if (Environment.GetEnvironmentVariable("REDPOINT_EOS_STRICT_BUILD") == "1")
		{
			CppStandard = CppStandardVersion.Cpp17;
			bUseUnity = false;
		}

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

			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"Engine",
					"CoreUObject",
					"OnlineSubsystem",
					"OnlineSubsystemUtils",
					"OnlineSubsystemRedpointEOS",
					"VoiceChat",
					"RedpointEOSSDK"
				}
			);
		}
		/* PRECOMPILED REMOVE END */
	}
}