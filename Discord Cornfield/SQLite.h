#pragma once
#include "include.h"

namespace SQLiteHelper {
	extern sqlite3* DataBase;
	extern bool Initialize();

	extern std::string GetPrefix(std::string ServerID);
	extern bool SetPrefix(std::string ServerID, std::string Prefix);
	
	extern int GetCookie(std::string UserID);
	extern int AddCookie(std::string UserID, int amount = 0, bool daily = false, bool remove = false);
	extern int StealCookies(std::string UserID, std::string EndID, int amount);
	extern int UpdateRobStatus(std::string UserID, bool robbed);

	extern ServerSetting GetServerSettings(std::string ServerID);
	extern int SetServerSetting(std::string ServerID, ServerSetting Settings);

	extern std::vector<WarningsList> GetWarnings(std::string ServerID, std::string UserID);
	extern bool SetWarnings(std::string ServerID, std::string UserID, std::string Warning);
	extern bool ClearWarnings(std::string ServerID, std::string UserID);
}