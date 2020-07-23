#include "include.h"
#include "api\user_api.h"

namespace OthersCommands {
	std::vector<CommandsFunctions> OtherCommands;
	void Initialize() {
		OtherCommands.push_back(CommandsFunctions("math", OthersMaths, "Tries to solve simple maths equations", "Other"));
		OtherCommands.push_back(CommandsFunctions("say", OthersSay, "Repeats what you say", "Other"));
		OtherCommands.push_back(CommandsFunctions("ping", OthersPing, "Pings the bot and returns the ping", "Other"));
		OtherCommands.push_back(CommandsFunctions("brainfuck", OthersBrainFuck, "Runs brainfuck code", "Other"));
		OtherCommands.push_back(CommandsFunctions("shortenlink", OthersShortenLink, "Shorten link", "Other"));
		OtherCommands.push_back(CommandsFunctions("help", OthersHelp, "Sends the command list for the bot", "Other"));
		OtherCommands.push_back(CommandsFunctions("prefix", OthersPrefix, "Shows the prefix of the server", "Other"));

		Commands::TotalCommands.push_back(OtherCommands);
	}

	void OthersPrefix(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		std::string ServerPrefix = SQLiteHelper::GetPrefix(message.guild().get()->serverid().to_string());
		return MessageWrap::EmbedReturn("This Server's Prefix is set to " + ServerPrefix, "You can use " + ServerPrefix + "setprefix to change the server's prefix!", message, timestamp);
	}

	void OthersMaths(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a maths equation you want me to solve", message, timestamp);

		std::size_t PrefixOffset = message.content().find(" ");
		std::string Message = message.content().substr(PrefixOffset, message.content().length());

		std::replace(Message.begin(), Message.end(), '`', ' ');
		double Answer = te_interp(Message.c_str(), 0);
		return MessageWrap::EmbedReturn("Maths", std::to_string(Answer), message, timestamp);
	}

	void OthersSay(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a message you want me to repeat", message, timestamp);

		std::size_t PrefixOffset = message.content().find(" ");
		std::string Message = message.content().substr(PrefixOffset, message.content().length());
		return MessageWrap::EmbedReturn("", Message, message, timestamp);
	}

	void OthersPing(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		return MessageWrap::EmbedReturn("Ping Pong", ":ping_pong: Pong", message, timestamp);
	}

	void OthersHelp(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2) {
			message.channel()->send_embed([&timestamp, &message](discord::Embed& e) {
				e.set_title("List of commands");

				std::string CommandHelp = "";
				std::string CommandSection = "";

				e.set_description("- To get help on an command type `" + SQLiteHelper::GetPrefix(message.guild()->serverid().to_string()) + "help <command>`");
				for (int i = 0; i < Commands::TotalCommands.size(); i++) {
					for (int j = 0; j < Commands::TotalCommands[i].size(); j++) {
						CommandSection = std::string(Commands::TotalCommands[i][j].Section + " Commands (" + std::to_string(Commands::TotalCommands[i].size()) + ")");
						CommandHelp += std::string("`" + Commands::TotalCommands[i][j].CommandName + "`, ");
					}
					e.add_field(CommandSection, CommandHelp, !Helpers::IsEven(i));
					CommandHelp.clear();
				}

				uint64_t CurrentTimeStamp = Helpers::TimeStamp();
				std::string TimeDifferent = std::to_string(CurrentTimeStamp - timestamp);
				e.set_footer(std::string("Took " + TimeDifferent + " ms to execute"));
			}).wait();
		}
		else {
			std::string HelpCommand = Param[1];
			for (int i = 0; i < Commands::TotalCommands.size(); i++) {
				for (int j = 0; j < Commands::TotalCommands[i].size(); j++) {
					if (HelpCommand == Commands::TotalCommands[i][j].CommandName) {
						return MessageWrap::EmbedReturn("Command Information", "`" + SQLiteHelper::GetPrefix(message.guild()->serverid().to_string()) + HelpCommand + "` - " + Commands::TotalCommands[i][j].CommandHelp, message, timestamp);
					}
				}
			}
			return MessageWrap::BasicEmbedReturn(true, "Command request not found!", message, timestamp);
		}
	}

	void OthersShortenLink(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a url you want me to shorten", message, timestamp);

		std::string URLShorted = WebHelp::ShortenURL(Param[1]);
		rapidjson::Document document;
		if (document.Parse(URLShorted.c_str()).HasParseError())
			return MessageWrap::BasicEmbedReturn(true, "Something went wrong! Error: 0x12", message, timestamp);

		if (!document.HasMember("url"))
			return MessageWrap::BasicEmbedReturn(true, "Something went wrong! Error: 0x13", message, timestamp);

		if (!document["url"].HasMember("status"))
			return MessageWrap::BasicEmbedReturn(true, "Something went wrong! Error: 0x14", message, timestamp);

		int ErrorCode = document["url"]["status"].GetInt();
		if (ErrorCode != 7)
			return MessageWrap::BasicEmbedReturn(true, std::string("Something went wrong! Error: 0x2" + std::to_string(ErrorCode)), message, timestamp);

		if (!document["url"].HasMember("shortLink"))
			return MessageWrap::BasicEmbedReturn(true, "Something went wrong! Error: 0x16", message, timestamp);

		std::string ShortURL = document["url"]["shortLink"].GetString();
		return MessageWrap::BasicEmbedReturn(false, std::string("Short Link: " + ShortURL), message, timestamp);
	}

	void OthersBrainFuck(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please type in brainfuck code to run!", message, timestamp);

		int Cycle = 0;
		std::string CommandCode = Param[1];
		std::string rOutput = Helpers::BrainFuckCompiler(CommandCode, Cycle);
		return MessageWrap::EmbedReturn("BrainFuck Compiler | " + std::to_string(Cycle) + " Cycles", rOutput, message, timestamp);
	}
}