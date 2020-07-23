#include "include.h"
#include <stack>
#include <iostream>
#include <cctype>
#include <cwctype>
#include <stdexcept>

namespace Helpers {
	void ClearConsole() {
        COORD topLeft = { 0, 0 };
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
            );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
            screen.dwSize.X * screen.dwSize.Y, topLeft, &written
            );

        SetConsoleCursorPosition(console, topLeft);
	}

    std::vector<std::string> SplitString(const std::string& str, const std::string& delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;
        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos) pos = str.length();
            std::string token = str.substr(prev, pos - prev);
            if (!token.empty()) tokens.push_back(token);
            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());
        return tokens;
    }

    bool IsNumber(const std::string& s) {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }

    std::string GetUserIDfromMention(std::string mention) {
        std::string Stripped = mention.substr(3, mention.length() - 4);
        if (IsNumber(mention))
            return mention;
        else if (IsNumber(Stripped))
            return Stripped;
        else
            return "";
    }

    std::string GetChannelIDfromMention(std::string mention) {
        std::string Stripped = mention.substr(2, mention.length() - 3);
        if (IsNumber(mention))
            return mention;
        else if (IsNumber(Stripped))
            return Stripped;
        else
            return "";
    }

    unsigned __int64 TimeStamp() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    }

    int64_t String2int64(const char* s) {
        int64_t i; char c;
        int scanned = sscanf(s, "%" SCNd64 "%c", &i, &c);
        if (scanned > 0) return i;
        return 0;
    }

    std::string RandomCharacterGen(int length) {
        srand(time(NULL));
        auto randchar = []() -> char
        {
            const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[rand() % max_index];
        };
        std::string str(length, 0);
        std::generate_n(str.begin(), length, randchar);
        return str;
    }

    int RandomNumberGen(int length, unsigned int seed) {
        if (!seed)
            srand(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
        else
            srand(seed);

        int Random = rand() % length + 1;
        return Random;
    }

    void ChecksStr(std::string& STR) {
        if (STR.length() > 1999) {
            STR.resize(1990);
            STR += "...";
        }
    }

    std::string CPUName() {
        // Get extended ids.
        int CPUInfo[4] = { -1 };
        __cpuid(CPUInfo, 0x80000000);
        unsigned int nExIds = CPUInfo[0];

        // Get the information associated with each extended ID.
        char CPUBrandString[0x40] = { 0 };
        for (unsigned int i = 0x80000000; i <= nExIds; ++i)
        {
            __cpuid(CPUInfo, i);

            // Interpret CPU brand string and cache information.
            if (i == 0x80000002)
            {
                memcpy(CPUBrandString,
                    CPUInfo,
                    sizeof(CPUInfo));
            }
            else if (i == 0x80000003)
            {
                memcpy(CPUBrandString + 16,
                    CPUInfo,
                    sizeof(CPUInfo));
            }
            else if (i == 0x80000004)
            {
                memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
            }
        }

        return CPUBrandString;
    }

    bool IsEven(int number) {
        return (number % 2 == 0);
    }

    std::string MockText(std::string Message) {
        std::string rMockTest = Message;
        for (int i = 0; i < Message.size(); i++) {
            int Random5050 = RandomNumberGen(2);
            if (Random5050 == 1)
                rMockTest.at(i) = toupper(Message.at(i));
            else
                rMockTest.at(i) = tolower(Message.at(i));
        }

        return rMockTest;
    }

    std::string BrainFuckCompiler(const std::string& commands, int& Cycle)
    {
        std::string EndMessage;
        std::vector<int> data(1, 0);
        std::vector<int>::iterator dataPtr = data.begin();

        std::string::const_iterator instructionPtr = commands.begin();
        std::stack<std::string::const_iterator> instructionStack;

        while (instructionPtr != commands.end())
        {
            if (Cycle > 10000)
                return ("Took too many cycles to run!");

            switch (*instructionPtr)
            {
            case '<':
            {
                dataPtr--;
                break;
            }
            case '>':
            {
                dataPtr++;
                if (dataPtr == data.end()) {
                    data.push_back(0);
                    dataPtr = data.end() - 1;
                }
                break;
            }
            case '+':
            {
                (*dataPtr) += 1;
                break;
            }
            case '-':
            {
                (*dataPtr) -= 1;
                break;
            }
            case '.':
            {
                EndMessage += char(*dataPtr);
                break;
            }
            case '[':
            {
                instructionStack.push(instructionPtr);

                if (*dataPtr == 0)
                {
                    auto startInstructionPtr = instructionPtr;
                    while (++instructionPtr != commands.end())
                    {
                        if (*instructionPtr == '[')
                            instructionStack.push(instructionPtr);
                        else if (*instructionPtr == ']')
                        {
                            if (instructionStack.empty())
                                return ("Found a ']' that did not have a matching '['!");

                            auto tempInstructionPtr = instructionStack.top();
                            instructionStack.pop();

                            if (startInstructionPtr == tempInstructionPtr)
                                break;
                        }
                    }
                }
                break;
            }
            case ']':
            {
                if (instructionStack.empty())
                    return ("Found a ']' that did not have a matching '['!");

                if (*dataPtr != 0)
                    instructionPtr = instructionStack.top();
                else
                    instructionStack.pop();

                break;
            }
            default:
                break;
            }
            instructionPtr++;
            Cycle++;

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        if (!instructionStack.empty())
            return ("Found a '[' that did not have a matching ']'!");

        return std::string(EndMessage);
    }

    bool HasAdminPermissions(discord::MessageEvent& message) {
        std::vector<discord::Snowflake> UserRoles = message.guild()->find_member(message.author().id())->get_roles();
        std::vector<discord::Role> GuildRoles = message.guild()->get_roles().get();

        for (int i = 0; i < GuildRoles.size(); i++) {
            for (int j = 0; j < UserRoles.size(); j++) {
                if (GuildRoles[i].get_id().id() == UserRoles[j].id()) {
                    if ((GuildRoles[i].get_permissions().get() & discord::PermissionFlag::ADMINISTRATOR) != 0) {
                        return true;
                    }
                }
            }
        }
        
        return false;
    }

    bool IsPremiumServer(std::string ServerID) {
        uint64_t iServerID = String2int64(ServerID.c_str());
        for (int i = 0; i < Settings::PremiumServers.size(); i++) {
            if (iServerID == Settings::PremiumServers[i])
                return true;
        }
        return false;
    }

    std::string RemoveDups(std::string content) {
        for (int i = 0; i < content.size(); ++i) {
            char check = content.at(i);
            for (int j = i + 1; j < content.size() - 1; ++j) {
                if (check == content.at(j)) {
                    content.erase(content.begin() + j);
                }
            }
        }
        return content;
    }

    std::string ReplaceStr(std::string str, const std::string& replace, char ch) {
        size_t i = str.find_first_of(replace);
        int found = str.find(replace);
        while (found != std::string::npos) {
            str[found] = ch;
            found = str.find_first_of(replace, found + 1);
        }

        return str;
    }
}