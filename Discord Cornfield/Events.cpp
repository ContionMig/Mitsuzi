#include "include.h"
#include "api\user_api.h"

namespace Events {
	std::map<uint64_t, ServerSetting> ServerSettings;
	std::map<uint64_t, std::string> ServerPrefixMap;
	std::map<uint64_t, std::string> ServerCoolDown;
	std::map<uint64_t, int> CookiesUsers;

	void Initialize(discord::Bot &Bot) {
		OnReady(Bot);
		OnMessage(Bot);
		OnEmoji(Bot);
		OnGuild(Bot);
	}

	void OnReady(discord::Bot& Bot) {
		Bot.on_ready([&Bot]() {
			while (!DiscordBot.profile().id().id())
				std::this_thread::sleep_for(std::chrono::milliseconds(500));

			if (!Threads::hReadyThread)
				Threads::hReadyThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Threads::ReadyStats, NULL, NULL, NULL);

			if (!Threads::hRefreshStats)
				Threads::hRefreshStats = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Threads::RefreshStats, NULL, NULL, NULL);

			if (!Threads::hSQLOperations)
				Threads::hSQLOperations = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Threads::SQLOperations, NULL, NULL, NULL);

			Settings::bBotSnowFlake = DiscordBot.profile().id();
			Settings::Ready = true;
		});
	}

	void OnMessage(discord::Bot& Bot) {
		Bot.on_message([&Bot](discord::MessageEvent& event) {
			if (event.author().bot())
				return;

			uint64_t NowTimeStamp = Helpers::TimeStamp();
			std::size_t SelfMention = event.content().find("<@!" + Settings::bBotSnowFlake.to_string() + ">");
			if (SelfMention != std::string::npos) {
				std::vector<std::string> Empty;
				return OthersCommands::OthersPrefix(event, Empty, Helpers::TimeStamp());
			}
			
			std::string ServerPrefix = Settings::bPrefix;
			discord::Snowflake ServerID = event.guild()->serverid();
			discord::Snowflake AuthorID = event.author().id();
			
			Functions::BasicPremium(AuthorID, ServerID, event);
			Functions::BasicSQLi::Basic(AuthorID);

			if (ServerPrefixMap.find(ServerID.id()) != ServerPrefixMap.end()) {
				ServerPrefix = ServerPrefixMap[ServerID.id()];
			}
			else if (ServerPrefixMap.find(ServerID.id()) == ServerPrefixMap.end()) {
				ServerPrefix = SQLiteHelper::GetPrefix(ServerID.to_string());
				ServerPrefixMap.insert(std::make_pair(ServerID.id(), ServerPrefix));
			}

			std::string Prefix = event.content().substr(0, ServerPrefix.length());
			if (Prefix != ServerPrefix || event.content().length() < (ServerPrefix.length() + 1))
				return;

			if (ServerCoolDown.find(AuthorID.id()) != ServerCoolDown.end()) {
				uint64_t TimeStamp = Helpers::String2int64(ServerCoolDown[AuthorID.id()].c_str());
				double TimeDifference = (NowTimeStamp - TimeStamp) / 1000.00;
				if (TimeDifference < Settings::UserCommandCooldown)
					return;

				ServerCoolDown[AuthorID.id()] = std::to_string(Helpers::TimeStamp());
			}
			else if (ServerCoolDown.find(AuthorID.id()) == ServerCoolDown.end()) {
				ServerCoolDown.insert(std::make_pair(AuthorID.id(), std::to_string(Helpers::TimeStamp())));
			}

			event.channel()->start_typing();
			std::string Content = event.content().substr(Prefix.length(), event.content().length());
			std::vector<std::string> SplitContent = Helpers::SplitString(Content, " ");
			Commands::MessageHandler(SplitContent, event, NowTimeStamp);
		});

		Bot.on_message_edited([](discord::MessageEvent& event) {

		});

		Bot.on_message_deleted([](discord::MessageDeletedEvent& event) {

		});
	}

	void OnEmoji(discord::Bot& Bot) {
		Bot.on_emoji_created([](discord::Emoji& event) {

		});

		Bot.on_emoji_deleted([](discord::Emoji& event) {

		});

		Bot.on_emoji_updated([](discord::Emoji& event) {

		});
	}

	void OnGuild(discord::Bot& Bot) {
		Bot.on_guild_created([](discord::Guild& event) {
			
		});

		Bot.on_presence([](discord::Presence& event) {

		});

		Bot.on_typing([](discord::TypingEvent& event) {

		});
	}
}