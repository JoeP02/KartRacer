// Copyright June Rhodes 2024. All Rights Reserved.

#include "RedpointEOSAPI/Templates/Converter.h"

namespace Redpoint::EOS::API
{

namespace Private
{

FString FApiCallNativeConverter::FromAnsi(const char *InString)
{
	if (InString == nullptr)
	{
        return FString();
	}

    return ANSI_TO_TCHAR(InString);
}

FString FApiCallNativeConverter::FromUtf8(const char* InString)
{
    if (InString == nullptr)
    {
        return FString();
    }

	return UTF8_TO_TCHAR((const UTF8CHAR *)InString);
}

} // namespace Private

} // namespace Redpoint::EOS::API