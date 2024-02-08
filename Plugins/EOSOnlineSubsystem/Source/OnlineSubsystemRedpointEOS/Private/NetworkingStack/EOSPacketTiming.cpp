// Copyright June Rhodes 2024. All Rights Reserved.

#include "./EOSPacketTiming.h"

#include "Containers/Array.h"
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Serialization/Archive.h"

#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
TAutoConsoleVariable<bool> CVarEOSEnablePacketTiming(
    TEXT("t.EOSEnablePacketTiming"),
    false,
    TEXT("When on, EOS includes timestamps as packets make their way through the system. This uses the tick/nanosecond "
         "measurement of the local computer, so reported values will only be correct when using play-in-editor. "
         "Connections to different computers will not be accurate as the clocks will not be in alignment."));

static TArray<TSharedRef<FEOSPacketTiming>> PacketTimingBuffer;

static TUniquePtr<FArchive> PacketTimingBufferFile;
#endif

#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
static void WritePacketTimingString(const FString &InString)
{
    if (PacketTimingBufferFile == nullptr)
    {
        FString SavedPath = FPaths::ProjectSavedDir() / TEXT("EOSPacketTiming.csv");
        PacketTimingBufferFile =
            TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*SavedPath, FILEWRITE_AllowRead));

        if (PacketTimingBufferFile == nullptr)
        {
            UE_LOG(LogRedpointEOS, Error, TEXT("Unable to write packet tracing file to path: %s"), *SavedPath);
        }
        else
        {
            UE_LOG(LogRedpointEOS, Verbose, TEXT("Writing packet tracing to: %s"), *SavedPath);
        }
    }

    if (PacketTimingBufferFile != nullptr)
    {
        FTCHARToUTF8 UTF8String(*InString);
        PacketTimingBufferFile->Serialize((UTF8CHAR *)UTF8String.Get(), UTF8String.Length() * sizeof(UTF8CHAR));
    }
}
#endif

void RecordPacketTiming(const TSharedPtr<FEOSPacketTiming> &InPacketTiming)
{
#if !(defined(UE_BUILD_SHIPPING) && UE_BUILD_SHIPPING)
    if (CVarEOSEnablePacketTiming.GetValueOnGameThread())
    {
        if (!InPacketTiming.IsValid())
        {
            return;
        }

        // If PulledFromQueue is MinValue, then this packet is being
        // acted upon right now (e.g. control channel packets).
        if (InPacketTiming->PulledFromQueue == FDateTime::MinValue())
        {
            InPacketTiming->PulledFromQueue = FDateTime::UtcNow();
        }

        if (PacketTimingBufferFile == nullptr)
        {
            WritePacketTimingString(TEXT(
                "Src User,Dest User,Socket Name,Channel,Bytes Sent,Sent At,Received At,Dequeued At,In Flight micros,In "
                "Queue micros,Latency micros,Latency ms\n"));
        }

        // PacketTimingBufferFile can still be null if the file can't be opened for writing.
        if (PacketTimingBufferFile != nullptr)
        {
            PacketTimingBuffer.Add(InPacketTiming.ToSharedRef());

            if (PacketTimingBuffer.Num() > 100)
            {
                for (const auto &Entry : PacketTimingBuffer)
                {
                    WritePacketTimingString(FString::Printf(
                        TEXT("%s,%s,%s,%u,%d,%lld,%lld,%lld,%f,%f,%f,%f\n"),
                        *Entry->SourceUserId,
                        *Entry->DestinationUserId,
                        *Entry->SymmetricSocketId,
                        Entry->SymmetricChannel,
                        Entry->Size,
                        Entry->Sent.GetTicks(),
                        Entry->ReceivedIntoQueue.GetTicks(),
                        Entry->PulledFromQueue.GetTicks(),
                        (Entry->ReceivedIntoQueue - Entry->Sent).GetTotalMicroseconds(),
                        (Entry->PulledFromQueue - Entry->ReceivedIntoQueue).GetTotalMicroseconds(),
                        (Entry->PulledFromQueue - Entry->Sent).GetTotalMicroseconds(),
                        (Entry->PulledFromQueue - Entry->Sent).GetTotalMilliseconds()));
                }

                PacketTimingBufferFile->Flush();
                PacketTimingBuffer.Empty();
            }
        }
    }
#endif
}