//
// Comment !hex {hexcolor} anywhere and the bot will answer accordingly
//

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>
#include <ruqquscpp/http.hpp>
#include <ruqquscpp/ruqqus.hpp>

int main(void) {
	// Create new client
	Ruqqus * client = new Ruqqus("https://ruqqus.com");
	
	client->client_id = "client_id";
	client->client_secret = "client_secret";
	client->refresh_token = "refresh_token";
	
	client->token = client->oauth_update_token();
	
	std::vector<std::string> id_list;
	id_list.push_back("0");
	
	try {
		for(;;) {
			// refresh token
			client->token = client->oauth_auto_update_token();
			
			// get newest comments
			std::vector<RuqqusComment> new_comments;
			new_comments = client->all_listing_comment("new","25","1");
			
			// Do we already have the comments?
			std::cout << "Obtaining next list of comments\r";
			for(size_t j = 0; j != new_comments.size(); j++) {
				size_t not_matching = 0;
				for(size_t i = 0; i != id_list.size(); i++) {
					if(new_comments[j].id != id_list[i]) {
						not_matching++;
					}
				}
				
				if(not_matching >= id_list.size()) {
					id_list.push_back(new_comments[j].id);
					
					// Check if it called our bot!
					if(new_comments[j].body.rfind("!hex",0) == 0) {
						std::cout << std::endl;
						std::cout << "Bot called !" << "+" << new_comments[j].guild_name
						<< " | by " << new_comments[j].author << ":" << new_comments[j].body << std::endl;
						
						// Yes, it called our bot, now get the hex cod
						// Use i_str as an immutable to not mute the
						// body property of new comments
						std::string i_str = new_comments[j].body;
						std::string hexcode;
						hexcode = i_str.substr(i_str.find(" ")+1);
						
						// Obtain response
						std::cout << "[" << new_comments[j].id << "]" << "Obtaining response" << std::endl;
						try {
							Json::Value val; Json::Reader read;
							std::string server_response; bool r;
							std::map<std::string,std::string> data;
							data.insert(std::pair<std::string,std::string>("hex",hexcode));
							server_response = http_get("https://colornames.org/search/json/",data);
							r = read.parse(server_response,val,false);
							if(!r) { throw std::runtime_error("Cannot parse JSON value"); }
							std::cout << "[" << new_comments[j].id << "]" << "Colornames.org returned " << server_response << std::endl;
							
							// Parse response
							std::string final_name;
							if(val["name"].isString()) {
								final_name = val["name"].asString();
							} else {
								throw std::runtime_error("Server did not return anything good!");
							}
							
							std::cout << "[" << new_comments[j].id << "]" << "Returning name of color: " << final_name << std::endl;
							
							client->comment_reply(new_comments[j].post,new_comments[j].id,"Thanks for calling! :), Your color is "+final_name+"\n\r\n\rI'm a bot");
						} catch(std::runtime_error& e) {
							std::cout << "[" << new_comments[j].id << "]" << "error with colornames.org:" << e.what() << std::endl;
						}
					}
				}
			}
			
			new_comments.clear();
			system("sleep 3");
		}
	} catch(std::runtime_error& e) {
		std::cout << "error:" << e.what() << std::endl;
	}
	delete client;
	return 0;
}
