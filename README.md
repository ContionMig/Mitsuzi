# Mitsuzi ( C++ Discord Bot )

[[My Website]](http://sagaanpillai.com/)

# Screenshots
![Screenshot](https://raw.githubusercontent.com/ContionMig/Mitsuzi/master/Discord%20Cornfield/Screenshots/Screenshot_3.png)

# Features
![Screenshot](https://github.com/ContionMig/Mitsuzi/blob/master/Discord%20Cornfield/Screenshots/Screenshot_1.png)

# Information / Important
Please note that this is not a simple compile and run project, i slightly modified libdiscord which you may need to do on your own as well to compile it properly. The code for the bot is really really messy at some places, such as the SQL parts. I made this bot in a couple of days, just to see if it was worth diving into making a bot using C, but it really wasn't worth it. In the end, i wasn't really happy with the results. 

# Libraries Used
- libdiscord: https://github.com/Roughsketch/libdiscord
- tinyexpr: https://github.com/codeplea/tinyexpr
- sqlite: https://www.tutorialspoint.com/sqlite/sqlite_c_cpp.htm
- curl: https://curl.haxx.se/
- brainfuck: https://github.com/texus/Brainfuck-interpreter

# SQL Tables
```
CREATE TABLE IF NOT EXISTS "serverinfo" (
	"serverid"	INTEGER,
	"prefix"	TEXT DEFAULT '++'
);
CREATE TABLE IF NOT EXISTS "warnings" (
	"serverid"	INTEGER DEFAULT 0,
	"userid"	INTEGER DEFAULT 0,
	"reason"	TEXT DEFAULT 'None',
	"timestamp"	INTEGER DEFAULT 0
);
CREATE TABLE IF NOT EXISTS "cookies" (
	"userid"	INTEGER DEFAULT 0,
	"amount"	INTEGER DEFAULT 0,
	"dailytimestamp"	INTEGER DEFAULT 0,
	"robbedcooldown"	INTEGER DEFAULT 0,
	"robcooldown"	INTEGER DEFAULT 0
);
CREATE TABLE IF NOT EXISTS "serversettings" (
	"serverid"	INTEGER,
	"badwordfilter"	INTEGER
);
```

# Settings
```
    std::string bToken = "FILL-ME-RIGHT-NOW";   // Bot Token - https://discord.com/developers/applications/
	std::string bPrefix = "++";                 // Bot default prefix ( may not be in synced with SQL database )
	std::string bServerDatabase = "database\\serverdatabase.db";    // Location of database
	int bShards = 1;                            // https://anidiots.guide/understanding/sharding

	float UserCommandCooldown = 2.0;            // Cooldown for command - each user
	int UserCookieBonus = 2;                    // Cookie bonus per message - each user

	uint64_t bOwnerID = 412144560190521366;     // Your user ID - you can use this to create owner's commands or smt
	uint64_t bOwnerGuid = 663397937895964672;   
	uint64_t bSuggestionChannel = 731402730253320274;
	uint64_t bJoinLeaveChannel = 731402748653994044;

    // some API keys which you can get for free
	std::string aCuttlyKey = "FILL-ME-RIGHT-NOW";
	std::string aGiphyKey = "FILL-ME-RIGHT-NOW";
	std::string aTheCatAPI = "FILL-ME-RIGHT-NOW";
	std::string aNewsAPI = "FILL-ME-RIGHT-NOW";

    // Used this for some premium commands, which i removed, but you can add your own if you want
	std::vector<uint64_t> PremiumServers = {
		663397937895964672,
		623154732009259018,
		637662554054852619,
		522682115519938560,
		595111006083088384
	};
```

# Notes
There is alot of things which should be changed / improved. I might recode it for a future release but, at this moment, i don't really see the point in recoding it unless there is a better library for it. 



