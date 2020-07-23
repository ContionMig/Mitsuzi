#include "include.h"

namespace MessageWrap {
	void BasicEmbedReturn(bool Error, std::string Disc, discord::MessageEvent& event, uint64_t timestamp) {
        Helpers::ChecksStr(Disc);
        event.channel()->send_embed([&Error, &Disc, &timestamp](discord::Embed& e) {
            if (Error)
                e.set_title(":red_circle: Error");
            else
                e.set_title(":green_circle: Success");

            e.set_description(Disc);

            uint64_t CurrentTimeStamp = Helpers::TimeStamp();
            std::string TimeDifferent = std::to_string(CurrentTimeStamp - timestamp);
            e.set_footer(std::string("Took " + TimeDifferent + " ms to execute"));
        });
	}

    void EmbedReturn(std::string title, std::string disc, discord::MessageEvent& event, uint64_t timestamp) {
        Helpers::ChecksStr(title);  Helpers::ChecksStr(disc);
        event.channel()->send_embed([&title, &disc, &timestamp](discord::Embed& e) {
            if (title.length() > 0)
                e.set_title(title);
            if (disc.length() > 0)
                e.set_description(disc);

            uint64_t CurrentTimeStamp = Helpers::TimeStamp();
            std::string TimeDifferent = std::to_string(CurrentTimeStamp - timestamp);
            e.set_footer(std::string("Took " + TimeDifferent + " ms to execute"));
        });
    }

    void EmbedLinkReturn(std::string title, std::string disc, std::string link, discord::MessageEvent& event, uint64_t timestamp) {
        Helpers::ChecksStr(title);  Helpers::ChecksStr(disc);
        event.channel()->send_embed([&title, &disc, &link, &timestamp](discord::Embed& e) {
            if (title.length() > 0)
                e.set_title(title);
            if (disc.length() > 0)
                e.set_description(disc);
            if (link.length() > 0)
                e.set_url(link);

            uint64_t CurrentTimeStamp = Helpers::TimeStamp();
            std::string TimeDifferent = std::to_string(CurrentTimeStamp - timestamp);
            e.set_footer(std::string("Took " + TimeDifferent + " ms to execute"));
        });
    }

    void EmbedImageReturn(std::string URL, discord::MessageEvent& event, uint64_t timestamp) {
        Helpers::ChecksStr(URL);
        event.channel()->send_embed([&URL, &timestamp](discord::Embed& e) {
            e.set_image(URL);

            uint64_t CurrentTimeStamp = Helpers::TimeStamp();
            std::string TimeDifferent = std::to_string(CurrentTimeStamp - timestamp);
            e.set_footer(std::string("Took " + TimeDifferent + " ms to execute"));
        });
    }
}