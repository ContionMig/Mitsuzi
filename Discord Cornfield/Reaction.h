#pragma once
#include "include.h"

namespace ReactionCommand {
	extern std::vector<CommandsFunctions> ReactionCommands;
	extern void Initialize();

	extern void ReactionAttack(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ReactionBite(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ReactionBlush(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ReactionBoop(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ReactionCringe(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ReactionCry(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ReactionFBI(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
}