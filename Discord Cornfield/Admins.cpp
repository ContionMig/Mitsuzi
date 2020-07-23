#include "include.h"
#include "api\user_api.h"

bool CompareTimestamp(WarningsList i1, WarningsList i2);
namespace AdminCommands {

	std::vector<CommandsFunctions> AdminCommands;
	void Initialize() {
		AdminCommands.push_back(CommandsFunctions("kick" , AdminKick, "Kicks a user", "Admin"));
		AdminCommands.push_back(CommandsFunctions("ban", AdminBan, "Bans a user", "Admin"));

		AdminCommands.push_back(CommandsFunctions("warn", AdminWarn, "Warns a user", "Admins"));
		AdminCommands.push_back(CommandsFunctions("warnlist", AdminWarnList, "Lists all warnings on a user", "Admin"));
		AdminCommands.push_back(CommandsFunctions("warnclear", AdminClearWarn, "Clears all warnings on a user", "Admin"));

		AdminCommands.push_back(CommandsFunctions("setprefix", AdminSetPrefix, "Sets the prefix for the server", "Admin"));
	
		Commands::TotalCommands.push_back(AdminCommands);
	}

	void AdminKick(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		std::vector<discord::Snowflake> UserRoles = message.guild().get()->find_member(message.author().id())->get_roles();
		std::vector<discord::Role> GuildRoles = message.guild().get()->get_roles().get();

		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		std::string KickUserID = Helpers::GetUserIDfromMention(Param[1]);
		if (!KickUserID.size())
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		bool bHasProperPerms = false;
		for (int i = 0; i < GuildRoles.size(); i++) {
			for (int j = 0; j < UserRoles.size(); j++) {
				if (GuildRoles[i].get_id().id() == UserRoles[j].id()) {
					if ((GuildRoles[i].get_permissions().get() & discord::PermissionFlag::ADMINISTRATOR) != 0 ||
						(GuildRoles[i].get_permissions().get() & discord::PermissionFlag::KICK_MEMBERS) != 0) {
						bHasProperPerms = true;
					}
				}
			}
		}

		if (!bHasProperPerms)
			return MessageWrap::BasicEmbedReturn(true, "You do not have the permission to use this command!", message, timestamp);

		discord::Member* KickUser = message.guild().get()->find_member(discord::Snowflake(KickUserID)).get();

		if (!KickUser)
			return MessageWrap::BasicEmbedReturn(true, "Please have an valid mention when using this command!", message, timestamp);
		
		if (message.guild().get()->kick(KickUser->user().id()).get())
			return MessageWrap::BasicEmbedReturn(false, "User has been kicked!", message, timestamp);
		else
			return MessageWrap::BasicEmbedReturn(true, "Unable to kick the user!", message, timestamp);
	}
	
	void AdminBan(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		std::vector<discord::Snowflake> UserRoles = message.guild().get()->find_member(message.author().id()).get()->get_roles();
		std::vector<discord::Role> GuildRoles = message.guild().get()->get_roles().get();

		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		std::string BanUserID = Helpers::GetUserIDfromMention(Param[1]);
		if (!BanUserID.size())
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		bool bHasProperPerms = false;
		for (int i = 0; i < GuildRoles.size(); i++) {
			for (int j = 0; j < UserRoles.size(); j++) {
				if (GuildRoles[i].get_id().id() == UserRoles[j].id()) {
					if ((GuildRoles[i].get_permissions().get() & discord::PermissionFlag::ADMINISTRATOR) != 0 || 
						(GuildRoles[i].get_permissions().get() & discord::PermissionFlag::BAN_MEMBERS) != 0) {
						bHasProperPerms = true;
					}
				}
			}
		}

		if (!bHasProperPerms)
			return MessageWrap::BasicEmbedReturn(true, "You do not have the permission to use this command!", message, timestamp);

		discord::Member* BanUser = message.guild().get()->find_member(discord::Snowflake(BanUserID)).get();

		if (!BanUser)
			return MessageWrap::BasicEmbedReturn(true, "Please have an valid mention when using this command!", message, timestamp);

		if (message.guild().get()->ban(BanUser->user().id(), 7).get())
			return MessageWrap::BasicEmbedReturn(false, "User has been banned!", message, timestamp);
		else
			return MessageWrap::BasicEmbedReturn(true, "Unable to ban the user!", message, timestamp);
	}

	void AdminWarn(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		std::vector<discord::Snowflake> UserRoles = message.guild().get()->find_member(message.author().id()).get()->get_roles();
		std::vector<discord::Role> GuildRoles = message.guild().get()->get_roles().get();

		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);
		else if (Param.size() < 3)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a reason you are warning this user", message, timestamp);

		std::string WarnUserID = Helpers::GetUserIDfromMention(Param[1]);
		if (!WarnUserID.size())
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		std::size_t PrefixOffset = message.content().find(" ");
		std::string WarningReason = message.content().substr(PrefixOffset + Param[1].size() + 1, message.content().length());

		if (WarningReason.size() < 3 ||
			WarningReason.size() > 200)
			return MessageWrap::BasicEmbedReturn(true, "Please make sure the reason is inbetween 3 - 200 characters!", message, timestamp);

		bool bHasProperPerms = false;
		for (int i = 0; i < GuildRoles.size(); i++) {
			for (int j = 0; j < UserRoles.size(); j++) {
				if (GuildRoles[i].get_id().id() == UserRoles[j].id()) {
					if ((GuildRoles[i].get_permissions().get() & discord::PermissionFlag::ADMINISTRATOR) != 0 || 
						(GuildRoles[i].get_permissions().get() & discord::PermissionFlag::KICK_MEMBERS) != 0) {
						bHasProperPerms = true;
					}
				}
			}
		}

		if (!bHasProperPerms)
			return MessageWrap::BasicEmbedReturn(true, "You do not have the permission to use this command!", message, timestamp);

		discord::Member* WarnUser = message.guild().get()->find_member(discord::Snowflake(WarnUserID)).get();

		if (!WarnUser)
			return MessageWrap::BasicEmbedReturn(true, "Please have an valid mention when using this command!", message, timestamp);

		if (SQLiteHelper::SetWarnings(message.guild().get()->serverid().to_string(), WarnUserID, WarningReason))
			return MessageWrap::BasicEmbedReturn(false, "You have warned the user!\nReason: " + WarningReason, message, timestamp);
		else
			return MessageWrap::BasicEmbedReturn(true, "Unable to handle request, SQL failure. Please contact bot owner!", message, timestamp);
	}

	void AdminWarnList(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		std::vector<discord::Snowflake> UserRoles = message.guild().get()->find_member(message.author().id()).get()->get_roles();
		std::vector<discord::Role> GuildRoles = message.guild().get()->get_roles().get();

		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		std::string WarnListUserID = Helpers::GetUserIDfromMention(Param[1]);
		if (!WarnListUserID.size())
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);

		bool bHasProperPerms = false;
		for (int i = 0; i < GuildRoles.size(); i++) {
			for (int j = 0; j < UserRoles.size(); j++) {
				if (GuildRoles[i].get_id().id() == UserRoles[j].id()) {
					if ((GuildRoles[i].get_permissions().get() & discord::PermissionFlag::ADMINISTRATOR) != 0 ||
						(GuildRoles[i].get_permissions().get() & discord::PermissionFlag::KICK_MEMBERS) != 0) {
						bHasProperPerms = true;
					}
				}
			}
		}

		if (!bHasProperPerms)
			return MessageWrap::BasicEmbedReturn(true, "You do not have the permission to use this command!", message, timestamp);

		discord::Member* WarnListUser = message.guild()->find_member(discord::Snowflake(WarnListUserID)).get();

		if (!WarnListUser)
			return MessageWrap::BasicEmbedReturn(true, "Please have an valid mention when using this command!", message, timestamp);

		std::vector<WarningsList> Warnings = SQLiteHelper::GetWarnings(message.guild().get()->serverid().to_string(), WarnListUserID);
		if (!Warnings.size())
			return MessageWrap::EmbedReturn("User's Warn List", "This user has no warnings!", message, timestamp);
		else {
			std::sort(Warnings.begin(), Warnings.end(), CompareTimestamp);
			message.channel()->send_embed([&message, &WarnListUser, &Warnings](discord::Embed& e) {
				e.set_title("USer's Warn List");

				int FieldSize = Warnings.size();
				if (FieldSize > 25)
					FieldSize = 25;

				for (int i = 0; i < FieldSize; i++) {
					std::string Field = std::string("Warning #" + std::to_string(Warnings.size() - i));
					e.add_field(Field, Warnings[i].WarningReason);
				}
				e.set_footer("Total Warnings: " + std::to_string(Warnings.size()));
			});
		}
	}

	void AdminClearWarn(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		std::vector<discord::Snowflake> UserRoles = message.guild().get()->find_member(message.author().id()).get()->get_roles();
		std::vector<discord::Role> GuildRoles = message.guild().get()->get_roles().get();

		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please mention the user which you like to clear warnings of!", message, timestamp);

		std::string WarnListUserID = Helpers::GetUserIDfromMention(Param[1]);
		if (!WarnListUserID.size())
			return MessageWrap::BasicEmbedReturn(true, "Please either mention the user or use their id for this command!", message, timestamp);


		bool bHasProperPerms = false;
		for (int i = 0; i < GuildRoles.size(); i++) {
			for (int j = 0; j < UserRoles.size(); j++) {
				if (GuildRoles[i].get_id().id() == UserRoles[j].id()) {
					if ((GuildRoles[i].get_permissions().get() & discord::PermissionFlag::ADMINISTRATOR) != 0 || 
						(GuildRoles[i].get_permissions().get() & discord::PermissionFlag::KICK_MEMBERS) != 0) {
						bHasProperPerms = true;
					}
				}
			}
		}

		if (!bHasProperPerms)
			return MessageWrap::BasicEmbedReturn(true, "You do not have the permission to use this command!", message, timestamp);

		discord::Member* WarnListUser = message.guild()->find_member(discord::Snowflake(WarnListUserID)).get();

		if (!WarnListUser)
			return MessageWrap::BasicEmbedReturn(true, "Please have an valid mention when using this command!", message, timestamp);

		std::vector<WarningsList> Warnings = SQLiteHelper::GetWarnings(message.guild().get()->serverid().to_string(), WarnListUserID);
		if (!Warnings.size())
			return MessageWrap::BasicEmbedReturn(true, "This user has no warnings to clear!", message, timestamp);
		else {
			if (SQLiteHelper::ClearWarnings(message.guild().get()->serverid().to_string(), WarnListUserID)) 
				return MessageWrap::BasicEmbedReturn(false, "Cleared all warnings from this user!", message, timestamp);
			else
				return MessageWrap::BasicEmbedReturn(true, "Unable to handle request, SQL failure. Please contact bot owner!", message, timestamp);
		}
	}

	void AdminSetPrefix(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp) {
		std::vector<discord::Snowflake> UserRoles = message.guild().get()->find_member(message.author().id()).get()->get_roles();
		std::vector<discord::Role> GuildRoles = message.guild().get()->get_roles().get();

		if (Param.size() < 2)
			return MessageWrap::BasicEmbedReturn(true, "Please enter a prefix you like to change it to!", message, timestamp);

		bool bHasProperPerms = false;
		for (int i = 0; i < GuildRoles.size(); i++) {
			for (int j = 0; j < UserRoles.size(); j++) {
				if (GuildRoles[i].get_id().id() == UserRoles[j].id()) {
					if ((GuildRoles[i].get_permissions().get() & discord::PermissionFlag::ADMINISTRATOR) != 0) {
						bHasProperPerms = true;
					}
				}
			}
		}

		if (!bHasProperPerms)
			return MessageWrap::BasicEmbedReturn(true, "You do not have the permission to use this command!", message, timestamp);

		std::string Prefix = Param[1];
		if (Prefix.length() > 5) 
			return MessageWrap::BasicEmbedReturn(true, "Suggested prefix is too long, please make sure its lesser than 5 characters", message, timestamp);

		discord::Snowflake ServerID = message.guild().get()->serverid();
		if (SQLiteHelper::SetPrefix(ServerID.to_string(), Prefix)) {
			Events::ServerPrefixMap.erase(ServerID.id());
			return MessageWrap::BasicEmbedReturn(false, "Prefix for this server has been set to " + Prefix, message, timestamp);
		}
		else
			return MessageWrap::BasicEmbedReturn(true, "Unable to handle request, SQL failure. Please contact bot owner!", message, timestamp);
	}
}

bool CompareTimestamp(WarningsList i1, WarningsList i2)
{
	return (i1.Timestamp > i2.Timestamp);
}