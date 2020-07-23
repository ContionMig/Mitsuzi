#include "include.h"

namespace Commands {
	std::vector<std::vector<CommandsFunctions>> TotalCommands;
	void Initialize(discord::Bot& Bot) {
		AdminCommands::Initialize();
		OthersCommands::Initialize();
		FunCommands::Initialize();
		CookiesCommands::Initialize();
		ReactionCommand::Initialize();
		ConversationCommand::Initialize();
		UtilityCommand::Initialize();
	}

	void MessageHandler(std::vector<std::string> message, discord::MessageEvent& event, uint64_t timestamp) {

		if (message.size() < 1)
			return;

		std::string Command = message[0];
		std::transform(Command.begin(), Command.end(), Command.begin(), 
			[](unsigned char c) { return std::tolower(c); });

		for (int i = 0; i < TotalCommands.size(); i++) {
			for (int j = 0; j < TotalCommands[i].size(); j++) {
				if (Command == TotalCommands[i][j].CommandName) {
					TotalCommands[i][j].Function(event, message, timestamp);
				}
			}
		}
	}
}