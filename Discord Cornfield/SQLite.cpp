#include "include.h"

int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++)
        std::cout << azColName[i] << ": " << argv[i] << std::endl;

    std::cout << std::endl;
    return 0;
}

namespace SQLiteHelper {
    sqlite3* DataBase;
    bool Initialize() {
        char* zErrMsg = 0;
        int rc;

        rc = sqlite3_config(SQLITE_CONFIG_SERIALIZED);
        if (rc != SQLITE_OK)
            printf("setting sqlite thread safe mode to serialized failed!!! return code: %d\n", rc);

        rc = sqlite3_open(Settings::bServerDatabase.c_str(), &DataBase);
        if (rc) {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(DataBase));
            sqlite3_close(DataBase);
            return false;
        }

        return true;
    }

    std::string GetPrefix(std::string ServerID) {
        std::string CheckTable = "SELECT * FROM serverinfo WHERE serverid = '" + ServerID + "'; ";
        std::string IntertNewServer = "INSERT INTO serverinfo VALUES('" + ServerID + "', '++'); ";
        std::string CheckRow = Settings::bPrefix;

        struct sqlite3_stmt* selectstmt;
        int result = sqlite3_prepare_v2(DataBase, CheckTable.c_str(), -1, &selectstmt, NULL);
        if (result == SQLITE_OK)
        {
            if (sqlite3_step(selectstmt) == SQLITE_ROW)
            {
                const unsigned char* Prefix = sqlite3_column_text(selectstmt, 1);
                CheckRow = std::string((const char*)(Prefix));
            }
            else
            {
                sqlite3_exec(DataBase, IntertNewServer.c_str(), callback, 0, NULL);
            }
        }
        sqlite3_finalize(selectstmt);
        return CheckRow;
    }

    bool SetPrefix(std::string ServerID, std::string Prefix) {
        std::string CurrentPrefix = GetPrefix(ServerID);
        std::string UpdateServerPrefix = "UPDATE serverinfo SET prefix = '" + Prefix + "' WHERE serverid = '" + ServerID + "'; ";

        int Results = sqlite3_exec(DataBase, UpdateServerPrefix.c_str(), callback, 0, NULL);
        if (Results)
            return false;
        else
            return true;
    }

    int GetCookie(std::string UserID) {
        int Cookies = 0;
        std::string CheckCookie = "SELECT * FROM cookies WHERE userid = '" + UserID + "'; ";
        std::string InsertCookieRow = "INSERT INTO cookies VALUES('" + UserID + "', '0', '0', '0', '0'); ";

        struct sqlite3_stmt* selectstmt;
        int result = sqlite3_prepare_v2(DataBase, CheckCookie.c_str(), -1, &selectstmt, NULL);
        if (result == SQLITE_OK)
        {
            if (sqlite3_step(selectstmt) == SQLITE_ROW)
            {
                const unsigned char* CookieAmount = sqlite3_column_text(selectstmt, 1);
                Cookies = std::stoi(std::string((const char*)(CookieAmount)));
            }
            else
            {
                sqlite3_exec(DataBase, InsertCookieRow.c_str(), callback, 0, NULL);
            }
        }
        sqlite3_finalize(selectstmt);
        return Cookies;
    }

    int AddCookie(std::string UserID, int amount, bool daily, bool remove) {
        int TotalCookie = 0;

        if (remove)
            TotalCookie = GetCookie(UserID) - amount;
        else
            TotalCookie = GetCookie(UserID) + amount;

        if (TotalCookie < 0)
            TotalCookie = 0;

        int64_t TimeStamp = Helpers::TimeStamp();
        int64_t LastTimeStamp = 0;

        std::string CheckTable = "SELECT * FROM cookies WHERE userid = '" + UserID + "'; ";
        struct sqlite3_stmt* selectstmt;
        int result = sqlite3_prepare_v2(DataBase, CheckTable.c_str(), -1, &selectstmt, NULL);
        if (result == SQLITE_OK) {
            if (sqlite3_step(selectstmt) == SQLITE_ROW) {
                const unsigned char* TimeStampSQL = sqlite3_column_text(selectstmt, 2);
                LastTimeStamp = Helpers::String2int64((const char*)(TimeStampSQL));
                if (daily) {
                    if ((TimeStamp - LastTimeStamp) < 21400000) {
                        return -1;
                    }
                    else {
                        std::string UpateCookies = "UPDATE cookies SET amount = '" + std::to_string(TotalCookie) +
                            "', dailytimestamp = '" + std::to_string(TimeStamp) + "' WHERE userid = '" + UserID + "';";
                        int Results = sqlite3_exec(DataBase, UpateCookies.c_str(), callback, 0, NULL);
                        if (Results)
                            return 0;
                        else
                            return 1;
                    }
                }
                else {
                    std::string UpateCookies = "UPDATE cookies SET amount = '" + std::to_string(TotalCookie) +
                        "', dailytimestamp = '" + (std::string)(const char*)(TimeStampSQL) + "' WHERE userid = '" + UserID + "';";
                    int Results = sqlite3_exec(DataBase, UpateCookies.c_str(), callback, 0, NULL);
                    if (Results)
                        return 0;
                    else
                        return 1;
                }
            }

            sqlite3_finalize(selectstmt);
        }
    }

    int UpdateRobStatus(std::string UserID, bool robbed) {
        int Rob = robbed ? 3 : 4;
        int64_t TimeStamp = Helpers::TimeStamp();
        int64_t LastTimeStamp = 0;

        std::string CheckTable = "SELECT * FROM cookies WHERE userid = '" + UserID + "'; ";
        struct sqlite3_stmt* selectstmt;
        int result = sqlite3_prepare_v2(DataBase, CheckTable.c_str(), -1, &selectstmt, NULL);
        if (result == SQLITE_OK) {
            if (sqlite3_step(selectstmt) == SQLITE_ROW) {
                const unsigned char* TimeStampSQL = sqlite3_column_text(selectstmt, Rob);
                LastTimeStamp = Helpers::String2int64((const char*)(TimeStampSQL));
                if (((TimeStamp - LastTimeStamp) < 21400000))
                    return -1;
                else {
                    std::string RobStr = robbed ? "robbedcooldown" : "robcooldown";
                    std::string UpateCookies = "UPDATE cookies SET " + RobStr + " = '" + std::to_string(TimeStamp) + "' WHERE userid = '" + UserID + "';";
                    int Results = sqlite3_exec(DataBase, UpateCookies.c_str(), callback, 0, NULL);
                    if (Results)
                        return 0;
                    else
                        return 1;
                }
            }

            sqlite3_finalize(selectstmt);
        }
    }

    int StealCookies(std::string UserID, std::string EndID, int amount) {
        if (GetCookie(EndID) < amount)
            return -2;

        if (UpdateRobStatus(UserID, false) == -1 || 
            UpdateRobStatus(EndID, true) == -1)
            return -1;

        return (AddCookie(UserID, amount, false, false) && AddCookie(EndID, amount, false, true));
    }

    ServerSetting GetServerSettings(std::string ServerID) {
        ServerSetting rServerSettings = { };
        std::string CheckServerSetting = "SELECT * FROM serversettings WHERE serverid = '" + ServerID + "'; ";
        std::string InsertServerSettingRow = "INSERT INTO serversettings VALUES('" + ServerID + "', '0'); ";

        struct sqlite3_stmt* selectstmt;
        int result = sqlite3_prepare_v2(DataBase, CheckServerSetting.c_str(), -1, &selectstmt, NULL);
        if (result == SQLITE_OK) {
            if (sqlite3_step(selectstmt) == SQLITE_ROW) {
                const unsigned char* BadWordFilterSQL = sqlite3_column_text(selectstmt, 1);
                rServerSettings.BadWordFilter = std::stoi(std::string((const char*)(BadWordFilterSQL)));

            }
            else {
                sqlite3_exec(DataBase, InsertServerSettingRow.c_str(), callback, 0, NULL);
                rServerSettings.BadWordFilter = 0;
            }
        }
        sqlite3_finalize(selectstmt);
        return rServerSettings;
    }

    int SetServerSetting(std::string ServerID, ServerSetting Settings) {
        std::string CheckTable = "SELECT * FROM serversettings WHERE serverid = '" + ServerID + "'; ";
        struct sqlite3_stmt* selectstmt;
        int result = sqlite3_prepare_v2(DataBase, CheckTable.c_str(), -1, &selectstmt, NULL);
        if (result == SQLITE_OK) {
            if (sqlite3_step(selectstmt) == SQLITE_ROW) {
                std::string UpateCookies = std::string("UPDATE serversettings SET badwordfilter = '" + std::to_string(Settings.BadWordFilter) +
                   "' WHERE serverid = '" + ServerID + "';");
                int Results = sqlite3_exec(DataBase, UpateCookies.c_str(), callback, 0, NULL);
                if (Results)
                    return 0;
                else
                    return 1;
            }
            sqlite3_finalize(selectstmt);
        }
    }

    std::vector<WarningsList> GetWarnings(std::string ServerID, std::string UserID) {
        std::vector<WarningsList> Warnings;
        std::string CheckTable = "SELECT * FROM warnings WHERE userid = '" + UserID + "' AND serverid = '" + ServerID + "'; ";

        struct sqlite3_stmt* selectstmt;
        int result = sqlite3_prepare_v2(DataBase, CheckTable.c_str(), -1, &selectstmt, NULL);
        if (result == SQLITE_OK) {
            while (sqlite3_step(selectstmt) == SQLITE_ROW) {
                const unsigned char* WarningsChar = sqlite3_column_text(selectstmt, 2);
                const unsigned char* WarningTimeStamp = sqlite3_column_text(selectstmt, 3);

                Warnings.push_back(WarningsList(std::string((const char*)(WarningsChar)), std::string((const char*)(WarningTimeStamp))));
            }
        }
        sqlite3_finalize(selectstmt);
        return Warnings;
    }

    bool SetWarnings(std::string ServerID, std::string UserID, std::string Warning) {
        std::string Timestamp = std::to_string(Helpers::TimeStamp());
        std::string UpdateServerPrefix = "INSERT INTO warnings VALUES('" + ServerID + "', '" + UserID + "', '" + Warning + "', '" + Timestamp + "'); ";

        int Results = sqlite3_exec(DataBase, UpdateServerPrefix.c_str(), callback, 0, NULL);
        if (Results)
            return false;
        else
            return true;
    }

    bool ClearWarnings(std::string ServerID, std::string UserID) {
        std::string DeleteWarnings = "DELETE FROM warnings WHERE userid='" + UserID + "' AND serverid=" + ServerID + ";";

        int Results = sqlite3_exec(DataBase, DeleteWarnings.c_str(), callback, 0, NULL);
        if (Results)
            return false;
        else
            return true;
    }
}