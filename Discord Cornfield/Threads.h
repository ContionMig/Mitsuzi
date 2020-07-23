#pragma once
#include "include.h"

#define DIV 1048576
#define WIDTH 7

namespace Threads {
	extern HANDLE hReadyThread;
	extern DWORD WINAPI ReadyStats();

	extern HANDLE hRefreshStats;
	extern DWORD WINAPI RefreshStats();

	extern HANDLE hSQLOperations;
	extern DWORD WINAPI SQLOperations();
}