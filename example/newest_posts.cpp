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
	client.client_id = "yourClientId";
	client.client_secret = "clientSecret";
	client.refresh_token = "refreshToken";
	
	std::vector<RuqqusPost> posts;
	
	// obtain newest posts
	for(;;) {
		// refresh token
		client.token = client.oauth_auto_update_token();
		
		// get posts
		posts = client.front_listing_post("new");
		for(auto& p: posts) {
			std::cout << "+" << p.guildname << " : " << p.title << " (Id: " << p.id << ")." << std::endl;
		}
		
		// wait 10 seconds before next update
		system("sleep 10");
	}
	return 0;
}
