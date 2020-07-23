#pragma once
#include "include.h"

#pragma comment(lib,"ws2_32.lib")

namespace WebHelp {
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	
	extern std::string GetRandomJokes();
	extern std::string GetRandomAdvise();
	extern std::string GetMeme();
	extern std::string ShortenURL(std::string URL);
	extern std::string GetGIF(std::string tag, bool NSFW = false);
	extern std::string RandomFact();
	extern std::string GetRandomInsult();
	extern std::string GetRandomShowerThoughts();

	extern bool GetNews(std::string headline, std::string& sources, std::string& link);
}