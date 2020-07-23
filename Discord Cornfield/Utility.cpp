#include "include.h"

namespace UtilityCommand {
	std::vector<CommandsFunctions> UtilityCommands;
	void Initialize() {
		UtilityCommands.push_back(CommandsFunctions("feedback", UtilityFeedback, "Sends a feedback report to the bot developers", "Utility"));
		UtilityCommands.push_back(CommandsFunctions("info", UtilityInfo, "Sends the status/info of the bot", "Utility"));
		UtilityCommands.push_back(CommandsFunctions("poll", UtilityPoll, "Sets up a poll where every parameter is a option", "Utility"));
		UtilityCommands.push_back(CommandsFunctions("invite", UtilityInvite, "Replies with the bot's invite link", "Utility"));

		Commands::TotalCommands.push_back(UtilityCommands);
	}

	void UtilityFeedback(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a feedback that you like to send to the developers", message, timestamp);

		std::size_t PrefixOffset = message.content().find(" ");
		std::string bMessage = message.content().substr(PrefixOffset, message.content().length());
		std::string Suggestor = message.author().distinct();
		std::string aMessage = Suggestor + ": " + bMessage;

		message.channel()->find_guild(Settings::bOwnerGuid)->find_channel(Settings::bSuggestionChannel)->send_message(aMessage);
		return MessageWrap::BasicEmbedReturn(false, "Your feedback has been sent to the bot developers!\nThank you", message, timestamp);
	}

	void UtilityInfo(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		message.channel()->send_embed([&timestamp](discord::Embed& e) {
			e.set_title("- Current Bot Info -");

			e.add_field("Servers", std::to_string(Settings::TotalServers), true);
			e.add_field("Channels", std::to_string(Settings::TotalChannels), true);
			e.add_field("Members", std::to_string(Settings::TotalMembers), true);

			e.add_field("Memory Used", std::to_string(Settings::MemoryStatus.dwMemoryLoad) + "%", true);
			e.add_field("Free Memory", std::to_string(Settings::MemoryStatus.ullAvailPhys / DIV) + " MB", true);
			e.add_field("Free Virtual Memory", std::to_string(Settings::MemoryStatus.ullAvailVirtual / DIV) + " MB", true);

			e.add_field("CPU Processer", "```" + Settings::CPUName + "```", true);

			uint64_t CurrentTimeStamp = Helpers::TimeStamp();
			std::string TimeDifferent = std::to_string(CurrentTimeStamp - timestamp);
			e.set_footer(std::string("Took " + TimeDifferent + " ms to execute"));
		}).wait();
	}

	void UtilityPoll(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 3)
			return MessageWrap::BasicEmbedReturn(true, "Usage: poll <name> <option1> <option2> etc.", message, timestamp);

		std::vector<std::string> OptionsPoll = {};
		std::string Title = Param[1];
		for (int i = 2; i < Param.size(); i++) {
			OptionsPoll.push_back(Param[i]);
		}

		std::string Message = "";
		for (int i = 0; i < OptionsPoll.size(); i++) {
			Message += Array::EmoteNumbers[i] + ": " + OptionsPoll[i] + "\n";
		}

		discord::Message rMessage = { };
		Helpers::ChecksStr(Title);  Helpers::ChecksStr(Message);
		message.channel()->send_embed([&rMessage, &Title, &Message, &timestamp](discord::Embed& e) {
			if (Title.length() > 0)
				e.set_title(Title);
			if (Message.length() > 0)
				e.set_description(Message);

			uint64_t CurrentTimeStamp = Helpers::TimeStamp();
			std::string TimeDifferent = std::to_string(CurrentTimeStamp - timestamp);
			e.set_footer(std::string("Took " + TimeDifferent + " ms to execute"));
		}).then([](discord::Message message) {
			
		});
	}

	void UtilityInvite(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedLinkReturn("Invite Link", "Click on the title to invite the bot into your own server!","https://discord.com/oauth2/authorize?client_id=725245167199584277&permissions=8&scope=bot",message,timestamp);
	}
}