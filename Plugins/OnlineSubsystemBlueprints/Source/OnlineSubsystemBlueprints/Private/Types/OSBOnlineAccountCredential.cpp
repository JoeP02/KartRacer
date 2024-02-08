// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBOnlineAccountCredential.h"

FOnlineAccountCredential FOnlineAccountCredential::FromNative(const FOnlineAccountCredentials &InCred)
{
    FOnlineAccountCredential Cred;
    Cred.Type = InCred.Type;
    Cred.Id = InCred.Id;
    Cred.Token = InCred.Token;
    return Cred;
}

FOnlineAccountCredentials FOnlineAccountCredential::ToNative()
{
    FOnlineAccountCredentials Cred;
    Cred.Type = this->Type;
    Cred.Id = this->Id;
    Cred.Token = this->Token;
    return Cred;
}