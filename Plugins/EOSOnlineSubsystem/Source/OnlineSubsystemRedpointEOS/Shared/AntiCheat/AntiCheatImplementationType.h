// Copyright June Rhodes 2024. All Rights Reserved.

#pragma once

/**
 * Represents the type of Anti-Cheat implementation being used. This prevents
 * undefined behaviour when editors connect to protected servers, by stopping
 * the editor Anti-Cheat from trying to talk to an EAC protected server.
 */
enum class EAntiCheatImplementationType : uint8
{
    // This game does not use Anti-Cheat.
    Null = 0x0,

    // The Anti-Cheat protocol is using full EAC or is a trusted client.
    EasyAntiCheat = 0x1,

    // The Anti-Cheat protocol is currently FEditorAntiCheat, and we don't
    // use the real EAC interfaces.
    Editor = 0x2,
};