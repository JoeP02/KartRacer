// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"

namespace Redpoint::EOS::Core
{

namespace Utils
{

class REDPOINTEOSCORE_API FRegulatedTicker : public TSharedFromThis<FRegulatedTicker>
{
private:
    TMap<FDelegateHandle, FTickerDelegate> RegisteredTickers;
    FTSTicker::FDelegateHandle GlobalHandle;
    int32 TicksPerSecond;
    float AccumulatedDeltaSeconds;
    float CounterAccumulatedSeconds;
    int32 InvocationCount;
    int32 InvocationCountThisSecond;

    bool Tick(float DeltaSeconds);

public:
    FRegulatedTicker(int32 InTicksPerSecond = 60);
    UE_NONCOPYABLE(FRegulatedTicker);
    ~FRegulatedTicker();

	static FRegulatedTicker &GetCoreTicker();

    FDelegateHandle AddTicker(const FTickerDelegate &InDelegate);
    void RemoveTicker(FDelegateHandle Handle);
};

} // namespace Utils

} // namespace Redpoint::EOS::Core