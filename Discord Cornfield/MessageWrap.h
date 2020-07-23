#pragma once
#include "include.h"

namespace MessageWrap {
	extern void BasicEmbedReturn(bool Error, std::string Disc, discord::MessageEvent& event, uint64_t timestamp);
	extern void EmbedReturn(std::string title, std::string disc, discord::MessageEvent& event, uint64_t timestamp);
	extern void EmbedImageReturn(std::string URL, discord::MessageEvent& event, uint64_t timestamp);
	extern void EmbedLinkReturn(std::string title, std::string disc, std::string link, discord::MessageEvent& event, uint64_t timestamp);
}