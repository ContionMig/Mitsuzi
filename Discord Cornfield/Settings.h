#pragma once
#include "include.h"

namespace Settings {
	extern std::string bToken;
	extern std::string bPrefix;
	extern std::string bServerDatabase;
	extern int bShards;

	extern float UserCommandCooldown;
	extern int UserCookieBonus;

	extern uint64_t bOwnerID;
	extern uint64_t bOwnerGuid;
	extern uint64_t bSuggestionChannel;
	extern uint64_t bJoinLeaveChannel;

	extern std::string aCuttlyKey;
	extern std::string aGiphyKey;
	extern std::string aTheCatAPI;
	extern std::string aNewsAPI;

	extern std::vector<uint64_t> PremiumServers;

	extern bool Ready;
	extern bool Quit;

	extern discord::Snowflake bBotSnowFlake;

	extern int TotalServers;
	extern int TotalChannels;
	extern int TotalMembers;
	extern int TotalRoles;

	extern std::string CPUName;

	extern MEMORYSTATUSEX MemoryStatus;
	extern std::string SomethingWentWrongGif;
	extern std::string SomethingWentWrong;
}

extern discord::Bot DiscordBot;