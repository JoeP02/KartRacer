// Copyright June Rhodes 2024. All Rights Reserved.

#include "OnlineSubsystemEOSEditorPrefs.h"

UOnlineSubsystemEOSEditorPrefs::UOnlineSubsystemEOSEditorPrefs(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer)
{
    bHideDropdownInEditorToolbar = false;
    bAutomaticallyConfigureProjectForEOS = true;
    CategoryName = FName(TEXT("LevelEditor"));
}