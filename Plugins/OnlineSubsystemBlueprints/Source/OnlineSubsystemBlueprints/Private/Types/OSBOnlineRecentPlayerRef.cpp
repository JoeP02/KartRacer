// Copyright June Rhodes 2023. All Rights Reserved.

#include "Types/OSBOnlineRecentPlayerRef.h"

UOnlineRecentPlayerRef *UOnlineRecentPlayerRef::FromRecentPlayer(const TSharedPtr<FOnlineRecentPlayer> &RecentPlayer)
{
    auto Ref = NewObject<UOnlineRecentPlayerRef>();
    Ref->RecentPlayer = RecentPlayer;
    Ref->AssignFromUser(RecentPlayer);
    return Ref;
}

FDateTime UOnlineRecentPlayerRef::GetLastSeen()
{
    return this->RecentPlayer->GetLastSeen();
}