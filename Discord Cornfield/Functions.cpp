#include "include.h"

namespace Functions {
	void BasicPremium(discord::Snowflake AuthorID, discord::Snowflake ServerID, discord::MessageEvent& event) {
		uint64_t NowTimeStamp = Helpers::TimeStamp();
		if (Helpers::IsPremiumServer(ServerID.to_string())) {
			ServerSetting CurrentServerSettings = {};
			std::string Content = event.content();

			std::transform(Content.begin(), Content.end(), Content.begin(),
				[](unsigned char c) { return std::tolower(c); });

			if (Events::ServerSettings.find(ServerID.id()) != Events::ServerSettings.end()) {
				CurrentServerSettings = Events::ServerSettings[ServerID.id()];
			}
			else if (Events::ServerSettings.find(ServerID.id()) == Events::ServerSettings.end()) {
				CurrentServerSettings = SQLiteHelper::GetServerSettings(ServerID.to_string());
				Events::ServerSettings.insert(std::make_pair(ServerID.id(), CurrentServerSettings));
			}
			
			if (CurrentServerSettings.BadWordFilter) {
				if (!Helpers::HasAdminPermissions(event)) {
					if (CurrentServerSettings.BadWordFilter == 1) {
						if (Functions::BadWordFilter::SimpleFilter(Content)) {
							event.channel()->remove_message(event.message_id());
							return;
						}
					}
					else if (CurrentServerSettings.BadWordFilter == 2) {
						if (Functions::BadWordFilter::AdvanceFilter(Content)) {
							event.channel()->remove_message(event.message_id());
							return;
						}
					}
				}
			}
		}
	}

	namespace BadWordFilter {
		bool SimpleFilter(std::string content) {
			return FindFilter(content);
		}

		float AdvanceFilter(std::string content) {
			float TotalConfidently = 0.0;

			if (FindFilter(content))
				TotalConfidently += 0.15;

			if (DupFilter(content))
				TotalConfidently += 0.15;

			if (RemoveSpace(content))
				TotalConfidently += 0.15;

			if (ReplaceSymbols(content))
				TotalConfidently += 0.15;

			if (RemoveSymbols(content))
				TotalConfidently += 0.15;

			if (AllFilters(content))
				TotalConfidently += 0.15;

			return (TotalConfidently > 0.15);
		}

		bool FindFilter(std::string content) {
			for (int i = 0; i != Array::WordFilterList.size(); i++) {
				if (Array::WordFilterList[i].size() > 0) {
					if (content.find(Array::WordFilterList[i]) != std::string::npos) {
						return true;
					}
				}
			}
			return false;
		}

		bool RemoveSpace(std::string content) {
			content.erase(std::remove_if(content.begin(), content.end(), isspace), content.end());
			return FindFilter(content);
		}

		bool DupFilter(std::string content) {
			return FindFilter(Helpers::RemoveDups(content));
		}

		bool ReplaceSymbols(std::string content) {
			std::map<std::string, char>::iterator it;
			for (it = Array::SymbolsFilterList.begin(); it != Array::SymbolsFilterList.end(); it++) {
				content = Helpers::ReplaceStr(content, it->first, it->second);
			}

			return FindFilter(content);
		}

		bool RemoveSymbols(std::string content) {
			std::replace_if(content.begin(), content.end(), [](char c) {return !std::isalnum(c); }, ' ');
			content.erase(std::remove_if(content.begin(), content.end(), isspace), content.end());
			return FindFilter(content);
		}

		bool AllFilters(std::string content) {
			


			return FindFilter(content);
		}
	}

	namespace BasicSQLi {
		void Basic(discord::Snowflake AuthorID) {
			if (Events::CookiesUsers.find(AuthorID.id()) != Events::CookiesUsers.end()) {
				Events::CookiesUsers[AuthorID.id()] += Settings::UserCookieBonus;
			}
			else if (Events::CookiesUsers.find(AuthorID.id()) == Events::CookiesUsers.end()) {
				Events::CookiesUsers.insert(std::make_pair(AuthorID.id(), Settings::UserCookieBonus));
			}
		}
	}

}