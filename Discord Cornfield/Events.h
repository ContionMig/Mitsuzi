#pragma once
#include "include.h"
#include "Struct.h"

namespace Events {
	extern void Initialize(discord::Bot& Bot);

	extern std::map<uint64_t, ServerSetting> ServerSettings;
	extern std::map<uint64_t, std::string> ServerPrefixMap;
	extern std::map<uint64_t, std::string> ServerCoolDown;
	extern std::map<uint64_t, int> CookiesUsers;

	extern void OnReady(discord::Bot& Bot);
	extern void OnMessage(discord::Bot& Bot);
	extern void OnEmoji(discord::Bot& Bot);
	extern void OnGuild(discord::Bot& Bot);
}