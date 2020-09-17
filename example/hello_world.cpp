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
	client.client_id = "yourClientId";
	client.client_secret = "clientSecret";
	client.refresh_token = "refreshToken";
	
	std::cout << "Hello bot world!" << std::endl;
	post_submit("","Hello World","Hello Bot world! :)","RuqqusAPI");
	return 0;
}
