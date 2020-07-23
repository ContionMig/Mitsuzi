#pragma once
#include "include.h"

namespace Helpers {
	extern void ClearConsole();
	extern std::vector<std::string> SplitString(const std::string& str, const std::string& delim);

    extern std::string GetChannelIDfromMention(std::string mention);
    extern std::string GetUserIDfromMention(std::string mention);
    
    extern bool IsNumber(const std::string& s);
    extern unsigned __int64 TimeStamp();

    extern int64_t String2int64(const char* s);
    extern std::string RandomCharacterGen(int length);
    extern int RandomNumberGen(int length, unsigned int seed = 0);
    extern void ChecksStr(std::string& STR);

    extern std::string CPUName();
    extern bool IsEven(int number);
    extern std::string MockText(std::string Message);
    extern std::string RemoveDups(std::string content);
    extern std::string ReplaceStr(std::string str, const std::string& replace, char ch);

    extern std::string BrainFuckCompiler(const std::string& commands, int& Cycle);
    extern bool HasAdminPermissions(discord::MessageEvent& message);
    extern bool IsPremiumServer(std::string ServerID);

    template <typename T>
    std::string to_string_with_precision(const T a_value, const int n = 6)
    {
        std::ostringstream out;
        out.precision(n);
        out << std::fixed << a_value;
        return out.str();
    }
}