#
# This script patches AutomationTool so that we can run scripts post-stage from a plugin.
#
param([Parameter(Mandatory=$false)][string] $ProjectDir)

$ErrorActionPreference = "Stop"

# Unreal Engine 5 messes up the PATH environment variable. Ensure we fix up PATH from the
# current system's settings.
$UserPath = ([System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::User))
$ComputerPath = ([System.Environment]::GetEnvironmentVariable("PATH", [System.EnvironmentVariableTarget]::Machine))
if ($UserPath.Trim() -ne "") {
    $env:PATH = "$($UserPath);$($ComputerPath)"
} else {
    $env:PATH = $ComputerPath
}

# Check to make sure we have a project directory.
if ($ProjectDir -eq $null -or $ProjectDir -eq "") {
    exit 0
}

# Check to see if our environment is turning off all automatic bootstrapping and Anti-Cheat features.
if ($env:REDPOINT_EOS_SKIP_STAGING_HOOK_INSTALLATION -eq "1") {
	Write-Host "Skipping staging hook installation because the environment variable REDPOINT_EOS_SKIP_STAGING_HOOK_INSTALLATION=1 is set."
	exit 0
}

# Check to see if the project is turning off all automatic bootstrapping and Anti-Cheat features.
if (Test-Path "$ProjectDir\Config\DefaultEngine.ini") {
	$DefaultEngineIni = Get-Content -Raw -Path "$ProjectDir\Config\DefaultEngine.ini"
	if ($DefaultEngineIni.IndexOf("SkipStagingHookInstallation=True", [StringComparison]::InvariantCultureIgnoreCase) -ne -1) {
		Write-Host "Skipping staging hook installation because your project has SkipStagingHookInstallation=True set in DefaultEngine.ini."
		exit 0
	}
}

# Set content into a file, retrying if the file is currently in use.
function Set-RetryableContent([string] $Path, [string] $Value) {
    while ($true) {
        try {
            Set-Content -Force -Path $Path -Value $Value
            break
        } catch {
            if ($_.ToString().Contains("Stream was not readable.")) {
                continue
            }
        }
    }
}

# Copy a file, if the content in the target does not match the source. This prevents
# updating timestamps when it's not necessary (and thus avoids unnecessary rebuilds).
function Copy-IfNotChanged([string] $SourcePath, [string] $TargetPath) {
    $SourceContent = Get-Content -Raw $SourcePath
    if (Test-Path $TargetPath) {
        if ((Get-Item $TargetPath) -is [system.IO.directoryinfo]) {
            Remove-Item -Path $TargetPath
        } else {
            $TargetContent = Get-Content -Raw $TargetPath
            if ($SourceContent -eq $TargetContent) {
                return;
            }
        }
    }
    if (!(Test-Path ([System.IO.Path]::GetDirectoryName("$TargetPath")))) {
        New-Item -ItemType Directory ([System.IO.Path]::GetDirectoryName("$TargetPath"))
    }
    Write-Host "Setting up $TargetPath..."
    Set-RetryableContent -Path $TargetPath -Value $SourceContent
}

# Copy a file (if it exists) into a target path, moving the current file at the target path (if it exists)
# to the backup path first.
function Copy-FileWithBackup([string] $SourcePath, [string] $TargetPath, [string] $BackupPath) {
    if (!(Test-Path $SourcePath)) {
        # Source file doesn't exist, so it can't be patched.
        Write-Host "warning: File '$SourcePath' doesn't exist, so it can't be copied to '$TargetPath'."
        return
    }
    if (Test-Path $TargetPath) {
        # Target already exists, move it into the backup path.
        Write-Host "Moving '$TargetPath' to '$BackupPath' to back it up..."
        Move-Item -Force "$TargetPath" "$BackupPath"
    }
    $TargetDir = [System.IO.Path]::GetDirectoryName($TargetPath)
    if (!(Test-Path $TargetDir)) {
        # Directory for target file doesn't exist, create it.
        Write-Host "Creating directory '$TargetDir'..."
        New-Item -ItemType Directory -Path "$TargetDir" -Force
    }
    Write-Host "Copying '$SourcePath' to '$TargetPath' to back it up..."
    Copy-Item -Force "$SourcePath" "$TargetPath"
}

# Locate the current engine, and ensure it is Unreal Engine 5.
$EngineDir = (Resolve-Path "$((Get-Location).Path)\..\..").Path
$IsUnrealEngine5 = $false
if (Test-Path "$EngineDir\Engine\Binaries\Win64\UnrealEditor-Cmd.exe") {
    $IsUnrealEngine5 = $true
}
if (Test-Path "$EngineDir\Engine\Build\Build.version") {
    if ((Get-Content -Raw "$EngineDir\Engine\Build\Build.version").Contains("`"MajorVersion`": 5")) {
        $IsUnrealEngine5 = $true
    }
}
if (!$IsUnrealEngine5) {
    Write-Host "warning: This plugin no longer supports Unreal Engine 4. Please upgrade to Unreal Engine 5. Anti-Cheat and EOS bootstrapper hooks will not be installed into the engine."
    exit 0
}

# Copy the staging hooks.
if ($ProjectDir -ne $null -and $ProjectDir -ne "") {
    Copy-IfNotChanged "$PSScriptRoot\PostStageHook.bat" "$ProjectDir\Build\NoRedist\PostStageHook.bat"
    Copy-IfNotChanged "$PSScriptRoot\PostStageHook.ps1" "$ProjectDir\Build\NoRedist\PostStageHook.ps1"
}

# Check to see if CopyBuildToStagingDirectory.Automation.cs is patched in the engine. If it isn't, 
# we need to patch AutomationTool and recompile it so we have a hook that we can use to modify the 
# project when it is staged (not when it's built, which is when we are running right now).
$CopyBuildScriptPath = "$EngineDir\Engine\Source\Programs\AutomationTool\Scripts\CopyBuildToStagingDirectory.Automation.cs"
$CopyBuildScriptBackupPath = "$EngineDir\Engine\Source\Programs\AutomationTool\Scripts\CopyBuildToStagingDirectory.Automation.cs.backup"
$CopyBuildScriptContent = Get-Content -Raw $CopyBuildScriptPath
$CopyBuildScriptContentOriginal = $CopyBuildScriptContent
$PatchVersionLevel = "None"
if (Test-Path "$EngineDir\Engine\Binaries\DotNET\UBT_EOS_PatchLevel.txt") {
    $PatchVersionLevel = (Get-Content -Raw -Path "$EngineDir\Engine\Binaries\DotNET\UBT_EOS_PatchLevel.txt" | Out-String).Trim()
}
if (!$CopyBuildScriptContent.Contains("// EOS Online Subsystem Anti-Cheat Hook 1.1") -or $PatchVersionLevel -ne "1.1") {
    Write-Host "Installing staging hooks into AutomationTool..."

    Get-ChildItem -Path "$EngineDir\Engine\Source\Programs\AutomationTool" -Recurse -Filter "*" | % {
        if ($_.IsReadOnly) {
            $_.IsReadOnly = $false
        }
    }
    Get-ChildItem -Path "$EngineDir\Engine\Source\Programs\DotNETCommon" -Recurse -Filter "*" | % {
        if ($_.IsReadOnly) {
            $_.IsReadOnly = $false
        }
    }
    Get-ChildItem -Path "$EngineDir\Engine\Source\Programs\UnrealBuildTool" -Recurse -Filter "*" | % {
        if ($_.IsReadOnly) {
            $_.IsReadOnly = $false
        }
    }

    if (Test-Path $CopyBuildScriptBackupPath) {
        # We previously installed an older hook. Use original to so we can re-patch.
        $CopyBuildScriptContent = Get-Content -Raw $CopyBuildScriptBackupPath
    }

    $Hook = @"
// EOS Online Subsystem Anti-Cheat Hook 1.1
// EOS BEGIN HOOK
private static void ExecuteProjectPostStageHook(ProjectParams Params, DeploymentContext SC)
{
    string StageHookPath = Path.Combine(SC.ProjectRoot.FullName, "Build", "NoRedist", "PostStageHook.bat");
    if (File.Exists(StageHookPath))
    {
        RunAndLog(CmdEnv, StageHookPath, "\"" + SC.StageDirectory + "\"", Options: ERunOptions.Default | ERunOptions.UTF8Output, EnvVars: new Dictionary<string, string>
        {
            { "TargetConfiguration", SC.StageTargetConfigurations.FirstOrDefault().ToString() },
            { "TargetPlatform", SC.StageTargetPlatform.PlatformType.ToString() },
        });
    }
}
// EOS END HOOK
"@
    $CopyBuildScriptContent = $CopyBuildScriptContent.Replace("public static void CopyBuildToStagingDirectory(", "$Hook`r`n`r`npublic static void CopyBuildToStagingDirectory(");
    $CopyBuildScriptContent = $CopyBuildScriptContent.Replace("ApplyStagingManifest(ParamsInstance, SC);", "ApplyStagingManifest(ParamsInstance, SC); ExecuteProjectPostStageHook(ParamsInstance, SC);");
    $CopyBuildScriptContent = $CopyBuildScriptContent.Replace("ApplyStagingManifest(Params, SC);", "ApplyStagingManifest(Params, SC); ExecuteProjectPostStageHook(Params, SC);");
    if (!(Test-Path $CopyBuildScriptBackupPath)) {
        Copy-Item -Force $CopyBuildScriptPath $CopyBuildScriptBackupPath
    }
    Set-RetryableContent -Path $CopyBuildScriptPath -Value $CopyBuildScriptContent

    $Success = $false
    Push-Location "$EngineDir\Engine\Build\BatchFiles"
    try {
        $env:ENGINE_PATH = $EngineDir
        $local:CopyRules = @(
            @{
                Source = "$PSScriptRoot\UE5\fastJSON.dll";
                Target = "$EngineDir\Engine\Binaries\ThirdParty\fastJSON\netstandard2.0\fastJSON.dll";
            },
            @{
                Source = "$PSScriptRoot\UE5\fastJSON.deps.json";
                Target = "$EngineDir\Engine\Binaries\ThirdParty\fastJSON\netstandard2.0\fastJSON.deps.json";
            }
        )
        if (Test-Path "$EngineDir\Engine\Source\Programs\Shared\EpicGames.Perforce.Native") {
            $local:CopyRules += @{
                Source = "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationUtils\EpicGames.Perforce.Native.dll";
                Target = "$EngineDir\Engine\Binaries\DotNET\EpicGames.Perforce.Native\win-x64\Release\EpicGames.Perforce.Native.dll";
            }
            $local:CopyRules += @{
                Source = "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationUtils\EpicGames.Perforce.Native.dylib";
                Target = "$EngineDir\Engine\Binaries\DotNET\EpicGames.Perforce.Native\mac-x64\Release\EpicGames.Perforce.Native.dylib";
            }
            $local:CopyRules += @{
                Source = "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationUtils\EpicGames.Perforce.Native.so";
                Target = "$EngineDir\Engine\Binaries\DotNET\EpicGames.Perforce.Native\linux-x64\Release\EpicGames.Perforce.Native.so";
            }
        }
        foreach ($CopyRule in $local:CopyRules) {
            if ($global:IsMacOS -or $global:IsLinux) {
                $CopyRule.Source = $CopyRule.Source.Replace("\", "/")
                $CopyRule.Target = $CopyRule.Target.Replace("\", "/")
            }
            if ((Test-Path -Path $CopyRule.Source) -and !(Test-Path -Path $CopyRule.Target)) {
                $local:TargetDir = [System.IO.Path]::GetDirectoryName($CopyRule.Target)
                if (!(Test-Path -Path $local:TargetDir)) {
                    New-Item -ItemType Directory -Path $local:TargetDir | Out-Null
                }
                Copy-Item -Force -Path $CopyRule.Source -Destination $CopyRule.Target
            }
        }

        Write-Host "UAT: Locating MSBuild..."
        $DotNetDirPath = "$EngineDir\Engine\Binaries\ThirdParty\DotNet"
        if (!(Test-Path $DotNetDirPath)) {
            Write-Host "warning: Expected .NET to be located underneath '$DotNetDirPath', but it wasn't found. We can't patch UBT, so the EOS bootstrapper and Anti-Cheat will not work."
            exit 0
        }
        $DotNetVersionFolder = Get-ChildItem -Path $DotNetDirPath | Select-Object -First 1
        if ($DotNetVersionFolder -eq $null) {
            Write-Host "warning: Expected .NET to be located underneath '$DotNetDirPath', but it wasn't found. We can't patch UBT, so the EOS bootstrapper and Anti-Cheat will not work."
            exit 0
        }
        $DotNetPath = "$($DotNetVersionFolder.FullName)\windows\dotnet.exe"
        if (!(Test-Path $DotNetPath)) {
            Write-Host "warning: Expected .NET to be located at '$DotNetPath', but it wasn't found. We can't patch UBT, so the EOS bootstrapper and Anti-Cheat will not work."
            exit 0
        }

        Write-Host "UAT: Switching to correct build directory..."
        Push-Location ..\..
        try {
            Write-Host "UAT: Restoring AutomationTool packages... (UE5)"
            & $DotNetPath msbuild /nologo /clp:ErrorsOnly /verbosity:quiet Source\Programs\AutomationTool\Scripts\AutomationScripts.Automation.csproj /property:Configuration=Development /property:Platform=AnyCPU /t:Restore "/property:OutputPath=$EngineDir\Engine\Binaries\DotNET_EOSPatched" "/property:ReferencePath=$EngineDir\Engine\Binaries\DotNET\AutomationScripts"
            if ($LASTEXITCODE -ne 0) {
                exit $LASTEXITCODE
            }
            Write-Host "UAT: Building AutomationTool binary... (UE5)"
            & $DotNetPath msbuild /nologo /clp:ErrorsOnly /verbosity:quiet Source\Programs\AutomationTool\Scripts\AutomationScripts.Automation.csproj /property:Configuration=Development /property:Platform=AnyCPU "/property:OutputPath=$EngineDir\Engine\Binaries\DotNET_EOSPatched" "/property:ReferencePath=$EngineDir\Engine\Binaries\DotNET\AutomationScripts"
            if ($LASTEXITCODE -ne 0) {
                exit $LASTEXITCODE
            }
        } finally {
            Pop-Location
        }
        if ($LASTEXITCODE -ne 0) {
            if ($LASTEXITCODE -eq 8) {
                # This is a soft failure. We don't want to block people building the game
                # outright when they are missing dependencies to install the hooks.
                exit 0
            }
            exit $LASTEXITCODE
        }
        Copy-FileWithBackup `
            -SourcePath "$EngineDir\Engine\Binaries\DotNET_EOSPatched\AutomationScripts.Automation.dll" `
            -TargetPath "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.dll" `
            -BackupPath "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.dll.old"
        Copy-FileWithBackup `
            -SourcePath "$EngineDir\Engine\Binaries\DotNET_EOSPatched\AutomationScripts.Automation.pdb" `
            -TargetPath "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.pdb" `
            -BackupPath "$EngineDir\Engine\Binaries\DotNET\AutomationTool\AutomationScripts\Scripts\AutomationScripts.Automation.pdb.old"
        Set-Content -Force -Path "$EngineDir\Engine\Binaries\DotNET\UBT_EOS_PatchLevel.txt" -Value "1.1"
        $Success = $true
    } finally {
        if (!$Success) {
            # Restore original script.
            Set-RetryableContent -Path $CopyBuildScriptPath -Value $CopyBuildScriptContentOriginal
        }
        Pop-Location
    }

    Write-Host "warning: EOS Online Subsystem had to patch your engine's CopyBuildToStagingDirectory.Automation.cs file to be compatible with Anti-Cheat and the EOS Bootstrapper Tool. Executables won't be correctly packaged until you next build and package the project."
    exit 0
}

exit 0