// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Interfaces/OnlineIdentityInterface.h"

#if EOS_GOOGLE_ENABLED

FORCEINLINE uint32 FUniqueNetIdRedpointGoogle_GetTypeHash(const FString &S)
{
    return GetTypeHash(S);
}

class FUniqueNetIdRedpointGoogle : public FUniqueNetId
{
private:
    FString UserId;

public:
    FUniqueNetIdRedpointGoogle();
    FUniqueNetIdRedpointGoogle(const FString &Id);
    UE_NONCOPYABLE(FUniqueNetIdRedpointGoogle);
    FString GetUserId() const;
    virtual FName GetType() const override;
    virtual const uint8 *GetBytes() const override;
    virtual int32 GetSize() const override;
    virtual bool IsValid() const override;
    virtual FString ToString() const override;
    virtual FString ToDebugString() const override;

    static const TSharedRef<const FUniqueNetId> &EmptyId();

    friend uint32 GetTypeHash(const FUniqueNetIdRedpointGoogle &A)
    {
        return FUniqueNetIdRedpointGoogle_GetTypeHash(A.UserId);
    }
    friend FArchive &operator<<(FArchive &Ar, FUniqueNetIdRedpointGoogle &OtherId)
    {
        return Ar << OtherId.UserId;
    }
};

#endif