//
// example00.cpp - repost xkcd comics, IF there is a new one
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
	int repostn = 0;
	Json::Value val; Json::Reader read;
	bool r; std::string server_response;
	std::string oldImg;
	
	// Place some stuffy
	client.client_id = client_id;
	client.client_secret = client_secret;
	client.refresh_token = refresh_token;

	// Initial refresh
	client.token = client.oauth_update_token();
	std::cout << "Auto refreshed token " << client.token << std::endl;
	
	start = std::chrono::steady_clock::now();
	for(;;) {
		// Check seconds passed (wait 1 minute before trying to post)
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		long int secs = std::chrono::duration_cast<std::chrono::seconds>(end-start).count();
		
		if(secs > 4) {
			std::cout << "5" << std::endl;
			
			// Get the HTTP response of XKCD via our API ;)
			server_response = http_get("https://xkcd.com/info.0.json");
			r = read.parse(server_response,val,false);
			if(!r) {
				throw std::runtime_error("Cannot parse JSON value");
			}
		
			// Obtain data from the JSON object
			std::string img = val["img"].asString();
			std::string name = val["safe_title"].asString();
			
			if(img != oldImg) {
				std::string url,title,body,guild;
				
				url = img;
				title = "[XKCD] - "+name;
				body = "bot-posted xkcd comic";
				guild = "general";
				
				client.post_submit(url,title,body,guild);
				std::cout << "posted xkcd "+img << std::endl;
				oldImg = img;
			}
			start = std::chrono::steady_clock::now();
		}
		
		// Auto update our token
		client.oauth_auto_update_token();
	}
	return 0;
}
