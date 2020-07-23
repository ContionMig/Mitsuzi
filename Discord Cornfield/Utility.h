#pragma once
#include "include.h"

namespace UtilityCommand {
	extern std::vector<CommandsFunctions> UtilityCommands;

	extern void Initialize();
	extern void UtilityFeedback(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void UtilityInfo(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void UtilityPoll(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void UtilityInvite(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
}