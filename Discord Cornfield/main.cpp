#include "include.h"

int main() {
    SetConsoleTitleA("Discord Bot");
    RegisterApplicationRestart(NULL, RESTART_NO_PATCH | RESTART_NO_REBOOT);

    if (SQLiteHelper::Initialize()) {
        Events::Initialize(DiscordBot);
        Commands::Initialize(DiscordBot);

        DiscordBot.run();
    }
    else {
        printf("Error! SQL could not boot up!");
    }

    while (!Settings::Quit)
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
}