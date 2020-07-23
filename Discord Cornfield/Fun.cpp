#include "include.h"

namespace FunCommands {
	std::vector<CommandsFunctions> FunCommands;
	void Initialize() {
		FunCommands.push_back(CommandsFunctions("dick" , FunDick, "Displays user's dick size", "Fun"));
		FunCommands.push_back(CommandsFunctions("talk", FunTalk, "Replies with a random talk", "Fun"));
		FunCommands.push_back(CommandsFunctions("insult", FunInsult, "Replies with a random insult", "Fun"));
		FunCommands.push_back(CommandsFunctions("joke", FunJoke, "Replies with a random joke", "Fun"));
		FunCommands.push_back(CommandsFunctions("iq", FunIQ, "Displays user's IQ", "Fun"));
		FunCommands.push_back(CommandsFunctions("gif", FunGIF, "Returns a gif from the tag", "Fun"));
		FunCommands.push_back(CommandsFunctions("meme", FunMeme, "Returns a random meme", "Fun"));
		FunCommands.push_back(CommandsFunctions("showerthought", FunShowerThoughts, "Replies with a random shower thought", "Fun"));
		FunCommands.push_back(CommandsFunctions("mock", FunMock, "Mocks the given text", "Fun"));

		Commands::TotalCommands.push_back(FunCommands);
	}

	void FunDick(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		srand(time(NULL));
		int RandomDickSize = Helpers::RandomNumberGen(15);

		std::string DickSize = "8";
		for (int i = 0; i < RandomDickSize; i++) {
			DickSize += "=";
		}
		DickSize += "D";

		return MessageWrap::EmbedReturn(message.author().name() + "'s Dick Size", DickSize, message, timestamp);
	}

	void FunIQ(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		srand(time(NULL));
		int RandomTalk = Helpers::RandomNumberGen(170);

		std::string Message = message.author().name() + "'s IQ is " + std::to_string(RandomTalk);
		return MessageWrap::EmbedReturn("", Message, message, timestamp);
	}

	void FunTalk(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		int RandomTalk = Helpers::RandomNumberGen(Array::FunTalkStr.size());

		char buff[1999];
		snprintf(buff, sizeof(buff), Array::FunTalkStr[RandomTalk].c_str(), message.author().name().c_str(), message.author().name().c_str(), message.author().name().c_str());
		std::string buffAsStdStr = buff;

		if (buffAsStdStr.size() > 1980)
			buffAsStdStr.resize(1980);

		return MessageWrap::EmbedReturn("Chit Chat", buffAsStdStr, message, timestamp);
	}

	void FunInsult(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedReturn("Chit Chat", WebHelp::GetRandomInsult(), message, timestamp);
	}

	void FunJoke(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedReturn("Joke Generator", WebHelp::GetRandomJokes(), message, timestamp);
	}

	void FunGIF(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a search tag you like me to look for", message, timestamp);

		bool NSFW = message.channel()->nsfw();
		return MessageWrap::EmbedImageReturn(WebHelp::GetGIF(Param[1], NSFW), message, timestamp);
	}

	void FunMeme(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedImageReturn(WebHelp::GetMeme(), message, timestamp);
	}

	void FunShowerThoughts(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedReturn("Chit Chat", WebHelp::GetRandomShowerThoughts(), message, timestamp);
	}

	void FunMock(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please type in the text you like to mock!", message, timestamp);

		std::size_t PrefixOffset = message.content().find(" ");
		std::string Message = message.content().substr(PrefixOffset, message.content().length());
		message.channel()->send_message(Helpers::MockText(Message));
	}
}

