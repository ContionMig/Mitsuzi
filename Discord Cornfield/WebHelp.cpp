#include "include.h"

namespace WebHelp {
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string GetRandomJokes() {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            struct curl_slist* hs = NULL;
            hs = curl_slist_append(hs, "Accept: text/plain");
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
            curl_easy_setopt(curl, CURLOPT_URL, "https://icanhazdadjoke.com/");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    std::string GetRandomAdvise() {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://api.adviceslip.com/advice");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        rapidjson::Document document;
        if (document.Parse(readBuffer.c_str()).HasParseError())
            return Settings::SomethingWentWrong;

        if (!document.HasMember("slip"))
            return Settings::SomethingWentWrong;

        if (!document["slip"].HasMember("advice"))
            return Settings::SomethingWentWrong;

        std::string ShortURL = document["slip"]["advice"].GetString();
        return ShortURL;
    }

    std::string ShortenURL(std::string URL) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        std::string URLShorten = "https://cutt.ly/api/api.php?key=" + Settings::aCuttlyKey + "&short=" + URL + "&name=" + Helpers::RandomCharacterGen(10);
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, URLShorten);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }
        return readBuffer;
    }

    std::string GetMeme() {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://meme-api.herokuapp.com/gimme");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        rapidjson::Document document;
        if (document.Parse(readBuffer.c_str()).HasParseError())
            return Settings::SomethingWentWrongGif;

        if (!document.HasMember("url"))
            return Settings::SomethingWentWrongGif;

        std::string ShortURL = document["url"].GetString();
        return ShortURL;
    }

    std::string GetGIF(std::string tag, bool NSFW) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        std::replace_if(tag.begin(), tag.end(), [](char c) {return !std::isalnum(c); }, ' ');
        tag.erase(std::remove_if(tag.begin(), tag.end(), isspace), tag.end());
        
        std::string URLShorten = "https://api.giphy.com/v1/gifs/random?api_key=" + Settings::aGiphyKey + "&tag=" + tag + "&rating=" + (NSFW ? "R" : "PG-13");
        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, URLShorten);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        rapidjson::Document document;
        if (document.Parse(readBuffer.c_str()).HasParseError())
            return Settings::SomethingWentWrongGif;

        if (readBuffer.length() < 110)
            return Settings::SomethingWentWrongGif;

        if (document["meta"]["status"].GetInt() != 200)
            return Settings::SomethingWentWrongGif;

        if (!document.HasMember("data"))
            return Settings::SomethingWentWrongGif;

        if (!document["data"].HasMember("images"))
            return Settings::SomethingWentWrongGif;

        if (!document["data"]["images"].HasMember("original"))
            return Settings::SomethingWentWrongGif;

        if (!document["data"]["images"]["original"].HasMember("url"))
            return Settings::SomethingWentWrongGif;

        std::string ShortURL = document["data"]["images"]["original"]["url"].GetString();
        return ShortURL;
    }

    std::string RandomFact() {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://pastebin.com/raw/HjenCRgB");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        std::vector<std::string> Facts = Helpers::SplitString(readBuffer, "|");
        int RandomTalk = Helpers::RandomNumberGen(Facts.size() - 1);
        return Facts[RandomTalk];
    }

    std::string GetRandomInsult() {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://evilinsult.com/generate_insult.php?lang=en&type=json");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        rapidjson::Document document;
        if (document.Parse(readBuffer.c_str()).HasParseError())
            return Settings::SomethingWentWrong;

        if (!document.HasMember("insult"))
            return Settings::SomethingWentWrong;

        std::string Insult = document["insult"].GetString();
        return Insult;
    }

    std::string GetRandomShowerThoughts() {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "https://www.reddit.com/r/showerthoughts.json");
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        rapidjson::Document document;
        if (document.Parse(readBuffer.c_str()).HasParseError())
            return Settings::SomethingWentWrong;

        const rapidjson::Value& a = document["data"]["children"];
        int Random = Helpers::RandomNumberGen(a.Size() - 1);
        if (a.Size() > 0) 
            return a[Random]["data"]["title"].GetString();

        return Settings::SomethingWentWrong;
    }

    bool GetNews(std::string headline, std::string& sources, std::string& link) {
        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            std::string URL = "http://newsapi.org/v2/everything?q=" + headline + "&from=2020-06-02&sortBy=publishedAt&apiKey=" + Settings::aNewsAPI;
            curl_easy_setopt(curl, CURLOPT_URL, URL);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        rapidjson::Document document;
        if (document.Parse(readBuffer.c_str()).HasParseError())
            return false;

        if (!document.HasMember("articles"))
            return false;

        const rapidjson::Value& a = document["articles"];
        if (a.Size() > 0) {
            int Random = Helpers::RandomNumberGen(a.Size() - 1);

            sources = a[Random]["description"].GetString();
            link = a[Random]["url"].GetString();
            return true;
        }

        return false;
    }
}