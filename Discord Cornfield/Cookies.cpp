#include "include.h"

namespace CookiesCommands {
	std::vector<CommandsFunctions> CookieCommands;
	void Initialize() {
		CookieCommands.push_back(CommandsFunctions("daily", CookieDaily, "Gives the user their daily cookie!", "Cookie"));
		CookieCommands.push_back(CommandsFunctions("bal", CookieBal, "Gives the user their daily cookie!", "Cookie"));
		CookieCommands.push_back(CommandsFunctions("rob", CookieRob, "Robs a user of your choice!", "Cookie"));

		Commands::TotalCommands.push_back(CookieCommands);
	}

	void CookieDaily(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		int DailyCookie = Helpers::RandomNumberGen(3000);
		std::string UserID = message.author().id().to_string();

		switch (SQLiteHelper::AddCookie(UserID, DailyCookie, true))
		{
		case 0:
			return MessageWrap::BasicEmbedReturn(true, "Unable to handle request, SQL failure. Please contact bot owner!", message, timestamp);
			break;
		case 1:
			return MessageWrap::BasicEmbedReturn(false, "You have gained " + std::to_string(DailyCookie) + " Cookies, check in again after 6 hours!", message, timestamp);
			break;
		case -1:
			return MessageWrap::BasicEmbedReturn(true, "Your daily is still in cooldown. Daily can only be used every 6 hours, please be patient!", message, timestamp);
			break;
		default:
			return MessageWrap::BasicEmbedReturn(true, "Unable to handle request. Please contact bot owner!", message, timestamp);
			break;
		}

	}

	void CookieBal(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2) {
			int Cookie = SQLiteHelper::GetCookie(message.author().id().to_string());
			MessageWrap::EmbedReturn(message.author().name() + "'s Balance", "**Wallet**: " + std::to_string(Cookie) + " Cookies", message, timestamp);
		}
		else {
			std::string BalUserID = Helpers::GetUserIDfromMention(Param[1]);
			if (!BalUserID.length())
				return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

			discord::Member* BalUser = message.guild().get()->find_member(discord::Snowflake(BalUserID)).get();

			if (!BalUser)
				return MessageWrap::BasicEmbedReturn(true, "Please have an valid mention when using this command!", message, timestamp);

			int Cookie = SQLiteHelper::GetCookie(BalUserID);
			MessageWrap::EmbedReturn("Their Balance", "**Wallet**: " + std::to_string(Cookie) + " Cookies", message, timestamp);
		}
	}

	void CookieRob(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		std::string RobbedUserID = Helpers::GetUserIDfromMention(Param[1]);
		if (!RobbedUserID.length())
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		discord::Member* RobbedUser = message.guild().get()->find_member(discord::Snowflake(RobbedUserID)).get();

		if (!RobbedUser)
			return MessageWrap::BasicEmbedReturn(true, "Please have an valid mention when using this command!", message, timestamp);
		
		discord::Snowflake User = message.author().id();
		int EndCookies = SQLiteHelper::GetCookie(RobbedUserID);
		int UserCookies = SQLiteHelper::GetCookie(User.to_string());
		if (EndCookies < 2500) {
			return MessageWrap::BasicEmbedReturn(true, "The person you are trying to rob has less than 2.5k cookies!", message, timestamp);
		}

		int RandomRob = Helpers::RandomNumberGen((float)EndCookies * 0.01);
		switch (SQLiteHelper::StealCookies(User.to_string(), RobbedUserID, RandomRob))
		{
		case -2:
			return MessageWrap::BasicEmbedReturn(true, "Unable to steal cookies, user does not have enough cookies!", message, timestamp);
			break;
		case 0:
			return MessageWrap::BasicEmbedReturn(true, "Unable to handle request, SQL failure. Please contact bot owner!", message, timestamp);
			break;
		case 1:
			return MessageWrap::BasicEmbedReturn(false, "You have robbed " + std::to_string(RandomRob) + " Cookies, rob again after 6 hours!", message, timestamp);
			break;
		case -1:
			return MessageWrap::BasicEmbedReturn(true, "Either you or the person you are trying to rob has a cooldown!", message, timestamp);
		default:
			return MessageWrap::BasicEmbedReturn(true, "Unable to handle request. Please contact bot owner!", message, timestamp);
			break;
		}
	}
}