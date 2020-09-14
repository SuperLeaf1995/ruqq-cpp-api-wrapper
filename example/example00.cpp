//
// example00.cpp - repost xkcd comics, IF there is a new one
//
// Compiling commands:
// g++ -Wall -Wextra -lruqqus -lcurlpp -ljsoncpp -O2 example00.cpp -o example00
// ./example00
//

#include <iostream>
#include <string>
#include <thread>
#include <jsoncpp/json/json.h>

#include <ruqquscpp/http.hpp>
#include <ruqquscpp/log.hpp>
#include <ruqquscpp/ruqqus.hpp>

std::string client_id = "yourClientId";
std::string client_secret = "clientSecret";
std::string refresh_token = "refreshToken";
std::string server = "https://ruqqus.com";
Ruqqus client(server);

int main(void) {
	// Credentials
	client.client_id = client_id;
	client.client_secret = client_secret;
	client.refresh_token = refresh_token;
	return 0;
}
