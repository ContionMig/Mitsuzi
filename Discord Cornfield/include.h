#pragma once
#define CURL_STATICLIB

#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <locale>

#include <stdint.h>

#include <discord.h>
#include <json.hpp>
#include <getRSS.h>

#include "sqlite\sqlite3.h"
#include "others\tinyexpr.h"

#include "cpprest\http_client.h"
#include "curl\curl.h"

#include "Settings.h"
#include "Events.h"
#include "Threads.h"
#include "Helpers.h"
#include "Commands.h"
#include "SQLite.h"
#include "MessageWrap.h"
#include "Array.h"
#include "WebHelp.h"
#include "Functions.h"