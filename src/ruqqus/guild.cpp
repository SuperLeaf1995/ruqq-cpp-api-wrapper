// std
#include <iostream>
#include <string>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/**
Gets the guild information from the official API

@param guildname The name of the board/guils to obtain data from it
*/
RuqqusGuild Ruqqus::guild_info(std::string guildname) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_get(server+"/api/v1/guild/"+guildname);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return JSON_to_guild(val);
}

/**
Gets guild listing
*/
std::vector<RuqqusGuild> Ruqqus::all_listing_guilds(std::string sort, std::string limit, std::string page) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	
	server_response = http_get(server+"/api/v1/guilds?sort="+sort+"&limit="+limit+"&page="+page);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	std::vector<RuqqusGuild> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["data"].size(); i++) {
		RuqqusGuild g;
		g = JSON_to_guild(val["data"][i]);
		ret.push_back(g);
	}
	return ret;
}

/**
Checks if guildname is available

@param guildname Name of the guild to be checked
@retval false Not available
@retval true Guild available
*/
bool Ruqqus::guild_available(std::string guildname) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_get(server+"/api/v1/board_available/"+guildname);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return val["available"].asBool();
}

/**
Joins guild <guildname>

@param guildname The name of the guild to join to
@retval true Sucess
@retval false Failure, Mostly because you are already in the guild
*/
bool Ruqqus::guild_join(std::string guildname) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_post(server+"/api/subscribe/"+guildname);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::string str = val["message"].asString();
	if(str.empty()) {
		return false;
	} else {
		return true;
	}
}

/**
Leaves guild <guildname>

@param guildname The name of the guild to leave
@retval true Sucess
*/
bool Ruqqus::guild_leave(std::string guildname) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_post(server+"/api/unsubscribe/"+guildname);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::string str = val["message"].asString();
	if(str.empty()) {
		return false;
	} else {
		return true;
	}
}
