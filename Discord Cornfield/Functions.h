#pragma once
#include "include.h"

namespace Functions {
	extern void BasicPremium(discord::Snowflake AuthorID, discord::Snowflake ServerID, discord::MessageEvent& event);
	
	namespace BadWordFilter {
		extern bool SimpleFilter(std::string content);
		extern float AdvanceFilter(std::string content);

		extern bool FindFilter(std::string content);
		extern bool RemoveSpace(std::string content);
		extern bool DupFilter(std::string content);
		extern bool ReplaceSymbols(std::string content);
		extern bool RemoveSymbols(std::string content);

		extern bool AllFilters(std::string content);
	}

	namespace BasicSQLi {
		extern void Basic(discord::Snowflake AuthorID);
	}
}
