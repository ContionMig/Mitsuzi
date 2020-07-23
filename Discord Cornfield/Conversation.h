#pragma once
#include "include.h"

namespace ConversationCommand {
	extern std::vector<CommandsFunctions> ConversationCommands;
	extern void Initialize();

	extern void ConversationTopic(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ConversationFact(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ConversationBall(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ConversationAdvise(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
	extern void ConversationNews(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp);
}