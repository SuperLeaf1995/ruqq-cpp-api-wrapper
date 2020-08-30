# ruqqus-cpp
Fanmade API made by me for using the ruqqus api

## Example ruqqus bot
```cpp
#include <ruqquscpp/ruqqus.hpp>
#include <ruqquscpp/http.hpp>

std::string server = "https://ruqqus.com";
Ruqqus client(server);

int main(int argc, char ** argv) {
	RuqqusGuild guild = client.guild_info("linux");

	// Print the guildname
	std::cout << guild.name << std::endl;
	
	// Print a wide line
	for(int i = 0; i < 40; i++) { std::cout << "="; }
	std::cout << std::endl;
	
	// Print the no. of users and other stats such as
	// description
	std::cout << guild.description << std::endl;
	std::cout << "[" << std::to_string(guild.mods_count) << " mods";
	std::cout << "] | [";
	std::cout << "[" << std::to_string(guild.subscriber_count) << " users";
	std::cout << "]" << std::endl;

	return 0;
}
```

## Installation

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
sudo make install
```

You're done! :)
