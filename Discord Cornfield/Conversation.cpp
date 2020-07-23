#include "include.h"

namespace ConversationCommand {
	std::vector<CommandsFunctions> ConversationCommands;
	void Initialize() {
		ConversationCommands.push_back(CommandsFunctions("topic", ConversationTopic, "Replies with a random topic", "Conversation"));
		ConversationCommands.push_back(CommandsFunctions("fact", ConversationFact, "Replies with a random fact", "Conversation"));
		ConversationCommands.push_back(CommandsFunctions("ball", ConversationBall, "Replied with a magic ball", "Conversation"));
		ConversationCommands.push_back(CommandsFunctions("advice", ConversationAdvise, "Replied with a random advice", "Conversation"));
		ConversationCommands.push_back(CommandsFunctions("news", ConversationNews, "Replies with the latest news on the topic", "Conversation"));

		Commands::TotalCommands.push_back(ConversationCommands);
	}

	void ConversationTopic(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF("attack", NSFW), message, timestamp);
	}

	void ConversationFact(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedReturn("Random Fact", WebHelp::RandomFact(), message, timestamp);
	}

	void ConversationBall(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a message for the 8 ball to answer!", message, timestamp);

		int RandomTalk = Helpers::RandomNumberGen(Array::Conversation8Ball.size());
		return MessageWrap::EmbedReturn("", "**8 Ball Says:** " + Array::Conversation8Ball[RandomTalk], message, timestamp);
	}

	void ConversationAdvise(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedReturn("Random Advice", WebHelp::GetRandomAdvise(), message, timestamp);
	}

	void ConversationNews(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a headline you would like to search for!", message, timestamp);

		std::string Discription, URL;
		if (WebHelp::GetNews(Param[1], Discription, URL))
			return MessageWrap::EmbedLinkReturn("Latest Headline:", Discription, URL, message, timestamp);
		else
			return MessageWrap::BasicEmbedReturn(true, "No results found for the headline requested!", message, timestamp);
	}
}