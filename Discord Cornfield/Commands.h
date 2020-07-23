#pragma once
#include "include.h"

#include "Admins.h"
#include "Others.h"
#include "Fun.h"
#include "Cookies.h"
#include "Reaction.h"
#include "Conversation.h"
#include "Utility.h"

namespace Commands {
	extern std::vector<std::vector<CommandsFunctions>> TotalCommands;
	extern void Initialize(discord::Bot& Bot);
	extern void MessageHandler(std::vector<std::string> message, discord::MessageEvent& event, uint64_t timestamp = Helpers::TimeStamp());
}