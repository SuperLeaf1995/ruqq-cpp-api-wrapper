//
// Auto updates token
//

#include <iostream>
#include <string>
#include <thread>
#include <jsoncpp/json/json.h>

#include <ruqquscpp/http.hpp>
#include <ruqquscpp/log.hpp>
#include <ruqquscpp/ruqqus.hpp>

int main(void) {
	// Create new client
	Ruqqus * client = new Ruqqus("https://ruqqus.com");
	client->client_id = "yourClientId";
	client->client_secret = "clientSecret";
	client->refresh_token = "refreshToken";
	
	try {
		// obtain newest posts
		for(;;) {
			// refresh token
			client->token = client->oauth_auto_update_token();
			
			std::string bname;
			std::cout << "Input name of guild" << std::endl;
			std::cin >> bname;
			if(client->guild_available(bname) == false) {
				std::cout << "Guild already taken!" << std::endl;
			} else {
				std::cout << "Guild is available!" << std::endl;
			}
		}
	} catch(std::runtime_exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	delete client;
	return 0;
}
