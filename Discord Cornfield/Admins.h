#pragma once
#include "include.h"
#include "Struct.h"

namespace AdminCommands {
	extern std::vector<CommandsFunctions> AdminCommands;
	extern void Initialize();

	extern void AdminKick(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void AdminBan(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	
	extern void AdminWarn(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void AdminWarnList(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void AdminClearWarn(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);

	extern void AdminSetPrefix(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
}