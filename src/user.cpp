// std
#include <iostream>
#include <string>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/**
Obtains information about current user
*/
RuqqusUser Ruqqus::user_me(void) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	std::map<std::string,std::string> data;

	server_response = http_get(server+"/api/v1/identity",data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	return JSON_to_user(val);
}

/**
Obtains information about username and returns a RuqqusUser class

@param username The name of the user to obtain information from it
*/
RuqqusUser Ruqqus::user_info(std::string username) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	
	std::map<std::string,std::string> data;

	server_response = http_get(server+"/api/v1/user/"+username,data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	return JSON_to_user(val);
}

/**
Obtains information about username and returns a RuqqusUser class

@param uid The id of the user to obtain information from it
*/
RuqqusUser Ruqqus::user_info_by_id(std::string uid) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	
	std::map<std::string,std::string> data;

	server_response = http_get(server+"/api/v1/user/by_id/"+uid,data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	return JSON_to_user(val);
}

/**
Checks if username is available

@param username Name of the user to be checked
@retval false Not available
@retval true User available
*/
bool Ruqqus::user_available(std::string username) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	std::map<std::string,std::string> data;

	server_response = http_get(server+"/api/v1/is_available/"+username,data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return val[username].asBool();
}

/**
Gets post listing in user
*/
std::vector<RuqqusPost> Ruqqus::user_listing_post(std::string username, std::string sort) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("sort",sort));
	
	server_response = http_get(server+"/api/v1/user/"+username+"/listing",data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	// The list is in negative order (from -24 to -0)
	std::vector<RuqqusPost> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["data"].size(); i++) {
		RuqqusPost post;
		post = JSON_to_post(val["data"][i]);
		ret.push_back(post);
	}
	return ret;
}

/**
Follows a user

@param username The username of the user
*/
void Ruqqus::user_follow(std::string username) {
	std::map<std::string,std::string> data;
	http_post(server+"/api/follow/"+username,data);
	return;
}

/**
Unfollows a user

@param username The username of the user
*/
void Ruqqus::user_unfollow(std::string username) {
	std::map<std::string,std::string> data;
	http_post(server+"/api/unfollow/"+username,data);
	return;
}

/**
Exiles a user from a board

@param username The username of the user
*/
void Ruqqus::user_exile(std::string username, std::string bid) {
	Json::Value val;
	Json::Reader read;
	bool r;
	std::string server_response;
	
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("username",username));
	
	server_response = http_post(server+"/mod/exile/"+bid,data);

	if(!server_response.empty()) {
		r = read.parse(server_response,val,false);
		if(!r) {
			throw std::runtime_error("Cannot parse JSON value");
		}

		// Server only returns a JSON of error when there is an error
		// if it does not return an error, we can safely assume that
		// it was a sucess
		std::string err = val["error"].asString();
		if(!err.empty()) {
			throw std::runtime_error("Server returned error "+err);
		}
	}

	return;
}
