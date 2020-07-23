#include "include.h"

namespace Settings {
	std::string bToken = "FILL-ME-RIGHT-NOW";
	std::string bPrefix = "++";
	std::string bServerDatabase = "database\\serverdatabase.db";
	int bShards = 1;

	float UserCommandCooldown = 2.0;
	int UserCookieBonus = 2;

	uint64_t bOwnerID = 412144560190521366;
	uint64_t bOwnerGuid = 663397937895964672;
	uint64_t bSuggestionChannel = 731402730253320274;
	uint64_t bJoinLeaveChannel = 731402748653994044;

	std::string aCuttlyKey = "FILL-ME-RIGHT-NOW";
	std::string aGiphyKey = "FILL-ME-RIGHT-NOW";
	std::string aTheCatAPI = "FILL-ME-RIGHT-NOW";
	std::string aNewsAPI = "FILL-ME-RIGHT-NOW";

	std::vector<uint64_t> PremiumServers = {
		663397937895964672,
		623154732009259018,
		637662554054852619,
		522682115519938560,
		595111006083088384
	};

	bool Ready = false;
	bool Quit = false;

	discord::Snowflake bBotSnowFlake;

	int TotalServers = 0;
	int TotalChannels = 0;
	int TotalMembers = 0;
	int TotalRoles = 0;

	std::string CPUName = Helpers::CPUName();

	MEMORYSTATUSEX MemoryStatus = {};
	std::string SomethingWentWrongGif = "https://media3.giphy.com/media/26uf6qaxqHpYXgjWU/giphy.gif?cid=ecf05e472f9638b0e9f3cab17a3aee9e8543e2e430e3525e&rid=giphy.gif";
	std::string SomethingWentWrong = "Seomthing Went Wrong!";
}

discord::Bot DiscordBot(Settings::bToken, Settings::bPrefix, Settings::bShards);