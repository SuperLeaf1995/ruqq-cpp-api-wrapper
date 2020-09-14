// std
#include <iostream>
#include <string>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/**
Generates a new token with OAuth. Token is returned as a std::string.
*/
std::string Ruqqus::oauth_update_token(void) {
	Json::Value val;
	Json::Reader read;
	bool r;
	std::string server_response;

	server_response = http_post(server+"/oauth/grant",
		"client_id="+client_id+
		"&client_secret="+client_secret+
		"&refresh_token="+refresh_token+
		"&grant_type=refresh");
	
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	std::string err = val["oauth_error"].asString();
	if(!err.empty()) {
		throw std::runtime_error("OAuth error: "+err);
	}

	std::string token = val["access_token"].asString();
	if(token.empty()) {
		throw std::runtime_error("Server threw invalid message");
	}

	http_set_oauth_token(token);
	return token;
}

/**
Generates a token via threading
*/
std::string Ruqqus::oauth_auto_update_token(void) {
	// Check if 1 hour passed and update token and chrono
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	long int secs = std::chrono::duration_cast<std::chrono::seconds>(end-oauth_start).count();
	if(secs > 3600) {
		// Start the chrono from now
		oauth_start = std::chrono::steady_clock::now();
		this->token = oauth_update_token();
	}
	return this->token;
}
