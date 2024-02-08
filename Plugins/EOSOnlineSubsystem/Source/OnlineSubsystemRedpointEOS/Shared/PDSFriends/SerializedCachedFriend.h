// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/Archive.h"

EOS_ENABLE_STRICT_WARNINGS

struct FSerializedCachedFriend
{
public:
    FString AccountId;
    TArray<uint8> AccountIdBytes;
    uint32 AccountIdTypeHash;
    FString AccountDisplayName;
    FString AccountRealName;
    FString ExternalAccountId;
    int32 ExternalAccountIdType;
    FString AccountAvatarUrl;
    FDateTime AccountAvatarUrlLastFetched;

    friend FArchive &operator<<(FArchive &Ar, FSerializedCachedFriend &Obj)
    {
        int8 Version = -1;
        if (Ar.IsSaving())
        {
            Version = 3;
        }
        Ar << Version;
        Ar << Obj.AccountId;
        Ar << Obj.AccountIdBytes;
        Ar << Obj.AccountIdTypeHash;
        Ar << Obj.AccountDisplayName;
        Ar << Obj.AccountRealName;
        Ar << Obj.ExternalAccountId;
        Ar << Obj.ExternalAccountIdType;
        if (Version >= 2)
        {
            Ar << Obj.AccountAvatarUrl;
        }
        if (Version >= 3)
        {
            Ar << Obj.AccountAvatarUrlLastFetched;
        }
        return Ar;
    }
};

EOS_DISABLE_STRICT_WARNINGS