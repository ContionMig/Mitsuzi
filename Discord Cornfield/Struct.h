#pragma once
#include "include.h"
#include <functional>

struct CommandsFunctions {
	std::string CommandName;
	std::function<void(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp)> Function;
	std::string CommandHelp;
	std::string Section;

	CommandsFunctions() {
		CommandName = "invalid";
		Function = 0;
		CommandHelp = "invalid";
		Section = "Others";
	}

	~CommandsFunctions() {

	}

	CommandsFunctions(std::string nCommandName, std::function<void(discord::MessageEvent& message, std::vector<std::string> Param, uint64_t timestamp)> nFunction, std::string nCommandHelp, std::string nSection = "Others") {
		CommandName = nCommandName;
		Function = nFunction;
		CommandHelp = nCommandHelp;
		Section = nSection;
	}
};

struct WarningsList {
	std::string WarningReason;
	std::string Timestamp;

	WarningsList(std::string nWarningReason, std::string nTimestamp) {
		WarningReason = nWarningReason;
		Timestamp = nTimestamp;
	}
};

struct ServerSetting {
	int BadWordFilter;

	ServerSetting() {
		BadWordFilter = -1;
	}

	~ServerSetting() {

	}

	ServerSetting(int nBadWordFilter) {
		BadWordFilter = nBadWordFilter;
	}

	bool empty() {
		if (BadWordFilter == -1)
			return true;
		return false;
	}
};