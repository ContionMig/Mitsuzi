#include "include.h"

namespace ReactionCommand {
	std::vector<CommandsFunctions> ReactionCommands;
	void Initialize() {
		ReactionCommands.push_back(CommandsFunctions("attack", ReactionAttack, "Sends an attack gif", "Reaction"));
		ReactionCommands.push_back(CommandsFunctions("bite", ReactionBite, "Sends a bite gif", "Reaction"));
		ReactionCommands.push_back(CommandsFunctions("blush", ReactionBlush, "Sends a blush gif", "Reaction"));
		ReactionCommands.push_back(CommandsFunctions("boop", ReactionBoop, "Sends a boop gif", "Reaction"));
		ReactionCommands.push_back(CommandsFunctions("cringe", ReactionCringe, "Sends a cringe gif", "Reaction"));
		ReactionCommands.push_back(CommandsFunctions("cry", ReactionCry, "Sends a cry gif", "Reaction"));
		ReactionCommands.push_back(CommandsFunctions("fbi", ReactionFBI, "FBI OPEN UP!", "Reaction"));

		Commands::TotalCommands.push_back(ReactionCommands);
	}

	void ReactionAttack(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF("attack", NSFW), message, timestamp);
	}

	void ReactionBite(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF("bite", NSFW), message, timestamp);
	}

	void ReactionBlush(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF("blush", NSFW), message, timestamp);
	}

	void ReactionBoop(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF("boop", NSFW), message, timestamp);
	}

	void ReactionCringe(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF("cringe", NSFW), message, timestamp);
	}

	void ReactionCry(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF("crying", NSFW), message, timestamp);
	}

	void ReactionFBI(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		int RandomFBIOpenUp = Helpers::RandomNumberGen(Array::TopReactionFBI.size());
		return MessageWrap::EmbedImageReturn(Array::TopReactionFBI[RandomFBIOpenUp], message, timestamp);
	}
}