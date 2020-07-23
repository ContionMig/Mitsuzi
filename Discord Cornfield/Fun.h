#pragma once
#include "include.h"

namespace FunCommands {
	extern std::vector<CommandsFunctions> FunCommands;
	extern void Initialize();

	extern void FunDick(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunTalk(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunInsult(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunIQ(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunJoke(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunGIF(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunMeme(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunShowerThoughts(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void FunMock(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
}
