//
// hello world!
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
		std::cout << "Hello bot world!" << std::endl;
		client->post_submit("","Hello World","Hello Bot world! :)","RuqqusAPI");
	} catch(std::runtime_exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	delete client;
	return 0;
}
