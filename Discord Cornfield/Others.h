#pragma once
#include "include.h"

namespace OthersCommands {
	extern std::vector<CommandsFunctions> OtherCommands;
	extern void Initialize();

	extern void OthersPrefix(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void OthersMaths(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void OthersSay(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void OthersPing(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void OthersHelp(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void OthersShortenLink(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void OthersBrainFuck(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
}