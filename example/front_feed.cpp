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
	
	std::vector<RuqqusPost> post;
	std::vector<std::string> id_list;
	
	id_list.push_back("0");
	
	client->token = client->oauth_update_token();
	
	try {
		// obtain newest posts
		for(;;) {
			// refresh token
			client->token = client->oauth_auto_update_token();
			
			// get posts
			post = client->all_listing_post("new","1","");
			
			size_t diff = 0;
			for(size_t i = 0; i < post.size(); i++) {
				for(size_t j = 0; j < id_list.size(); j++) {
					if(post[i].id != id_list[j]) {
						diff++;
					}
				}
				
				if(diff == id_list.size()) {
					id_list.push_back(post[i].id);
					std::cout << "+" << post[i].guild_name;
					std::cout << "\r\t\t:" << post[i].title;
					if(!post[i].url.empty()) {
						std::cout << " (" + post[i].url + ")";
					}
					std::cout << '\x07'; // produce a beep :)
					std::cout << std::endl;
				}
			}
			
			post.clear();
			
			// wait 10 seconds before next update
			system("sleep 1");
		}
	} catch(std::runtime_error& e) {
		std::cout << e.what() << std::endl;
	}
	
	post.clear();
	delete client;
	return 0;
}
