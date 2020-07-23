#pragma once
#include "include.h"

namespace CookiesCommands {
	extern std::vector<CommandsFunctions> CookieCommands;
	extern void Initialize();

	extern void CookieDaily(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void CookieBal(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void CookieRob(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
}