#include "include.h"

namespace Threads {

	HANDLE hReadyThread = NULL;
	DWORD WINAPI ReadyStats() {
		while (!Settings::Quit) {
			printf("-============- Current Bot Info -============-\n");
			printf("\nBot Info: \n");
			printf("Total Servers:            %d\n", Settings::TotalServers);
			printf("Total Channels:           %d\n", Settings::TotalChannels);
			printf("Total Members:            %d\n", Settings::TotalMembers);
			printf("Total Roles:              %d\n", Settings::TotalRoles);

			printf("\nMemory: \n");
			printf("Memory Percentage Used:   %ld \n", Settings::MemoryStatus.dwMemoryLoad);
			printf("Free Memory:              %d MB\n", Settings::MemoryStatus.ullAvailPhys / DIV);
			printf("Free Paging File:         %d MB\n", Settings::MemoryStatus.ullAvailPageFile / DIV);
			printf("Free Virtual Memory:      %d MB\n", Settings::MemoryStatus.ullAvailVirtual / DIV);

			std::this_thread::sleep_for(std::chrono::milliseconds(20000));
			Helpers::ClearConsole();
		}
		return 0;
	}

	HANDLE hRefreshStats = NULL;
	DWORD WINAPI RefreshStats() {
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
		while (!Settings::Quit) {
			Settings::TotalMembers = 0;
			Settings::TotalRoles = 0;

			Settings::TotalServers = DiscordBot.guilds().size();
			Settings::TotalChannels = DiscordBot.channels().size();

			for (int i = 0; i < DiscordBot.guilds().size(); i++) {
				Settings::TotalMembers += (int)DiscordBot.guilds()[i].member_count();
				Settings::TotalRoles += (int)DiscordBot.guilds()[i].get_roles().get().size();
			}

			Settings::MemoryStatus.dwLength = sizeof(Settings::MemoryStatus);
			GlobalMemoryStatusEx(&Settings::MemoryStatus);
			std::this_thread::sleep_for(std::chrono::milliseconds(60000));
		}
		return 0;
	}

	HANDLE hSQLOperations = NULL;
	DWORD WINAPI SQLOperations() {
		std::this_thread::sleep_for(std::chrono::milliseconds(4000));
		while (!Settings::Quit) {
			for (std::map<uint64_t, int>::iterator it = Events::CookiesUsers.begin(); it != Events::CookiesUsers.end(); it++) {
				if (it->first > 0) {
					SQLiteHelper::AddCookie(std::to_string(it->first), it->second, false, false);
					Events::CookiesUsers[it->first] = 0;
				}
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(10000));
		}
		return 0;
	}
}