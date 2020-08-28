# ruqq-cpp-api-wrapper
Fanmade API made by me for using the ruqqus api

## Example ruqqus bot
```cpp
#include <rcpp/ruqqus.hpp>
#include <rcpp/http.hpp>

int main(int argc, char ** argv) {
	std::string server = "https://ruqqus.com";
	Ruqqus client(server);
	
	RuqqusGuild guild = client.guild_info(std::string("linux"));

	std::cout << guild.name << std::endl;
	for(int i = 0; i < 80; i++) { std::cout << "="; }
	std::cout << guild.description << std::endl;
	std::cout << "[" << std::to_string(guild.mods_count) << " mods";
	std::cout << "] | [";
	std::cout << "[" << std::to_string(guild.subscriber_count) << " users";
	std::cout << "]" << std::endl;

	return 0;
}
```
