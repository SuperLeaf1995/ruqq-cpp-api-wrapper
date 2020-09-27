// std
#include <iostream>
#include <string>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/*
Administrative functions

These functions have not been tested, but with the correct admin levels
it should work theorically.
*/

/**
Bans a user. Requires 3 admin privileges

@param uid The Id of the user
@param reason Reason for ban
*/
void Ruqqus::admin_ban_user(std::string uid, int days, std::string reason, std::string message) {
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("reason",reason));
	data.insert(std::pair<std::string,std::string>("message",message));
	data.insert(std::pair<std::string,std::string>("days",std::to_string(days)));
	http_post(server+"/api/ban_user/"+uid,data);
	return;
}

/**
Unbans a user. Requires 3 admin privileges

@param uid The Id of the user
*/
void Ruqqus::admin_unban_user(std::string uid, bool unban_alts) {
	// Faster than std::boolalpha :P
	std::string alt;
	if(unban_alts) {
		alt = "true";
	} else {
		alt = "false";
	}
	
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("alts",alt));

	http_post(server+"/api/unban_user/"+uid,data);
	return;
}

/**
Bans a post. Requires 3 admin privileges

@param pid The Id of the post
@param reason Reason for ban
*/
void Ruqqus::admin_ban_post(std::string pid, std::string reason) {
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("reason",reason));
	
	http_post(server+"/api/ban_post/"+pid,data);
	return;
}

/**
Unbans a post. Requires 3 admin privileges

@param pid The Id of the post
*/
void Ruqqus::admin_unban_post(std::string pid) {
	std::map<std::string,std::string> data;
	
	http_post(server+"/api/unban_post/"+pid,data);
	return;
}

/**
Makes a post sticky. Requires 3 admin privileges

@param pid The Id of the post
*/
void Ruqqus::admin_sticky_post(std::string pid) {
	std::map<std::string,std::string> data;
	
	http_post(server+"/api/sticky_post/"+pid,data);
	return;
}

/**
Bans a comment. Requires 4 admin privileges

@param cid The Id of the comment
*/
void Ruqqus::admin_ban_comment(std::string cid) {
	std::map<std::string,std::string> data;
	
	http_post(server+"/api/ban_comment/"+cid,data);
	return;
}

/**
Unbans a comment. Requires 4 admin privileges

@param cid The Id of the comment
*/
void Ruqqus::admin_unban_comment(std::string cid) {
	std::map<std::string,std::string> data;
	
	http_post(server+"/api/unban_guild/"+cid,data);
	return;
}

/**
Bans a guild. Requires 4 admin privileges

@param bid The Id of the board
@param reason Reason for ban
*/
void Ruqqus::admin_ban_guild(std::string bid, std::string reason) {
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("reason",reason));
	
	http_post(server+"/api/ban_guild/"+bid,data);
	return;
}

/**
Unbans a guild. Requires 4 admin privileges

@param bid The Id of the board
*/
void Ruqqus::admin_unban_guild(std::string bid) {
	std::map<std::string,std::string> data;
	
	http_post(server+"/api/unban_guild/"+bid,data);
	return;
}

/**
Becomes mod of the board automatically. Requires 4 admin privileges

@param bid The Id of the board
*/
void Ruqqus::admin_mod_self(std::string bid) {
	std::map<std::string,std::string> data;
	
	http_post(server+"/api/mod_self/"+bid,data);
	return;
}

/**
Obatains all user status. Requires 2 admin privileges

@param days N. of days of data to be received
*/
Json::Value Ruqqus::admin_user_stat(int days) {
	Json::Value val;
	Json::Reader read;
	bool r;
	std::string server_response;
	
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("days",std::to_string(days)));
	
	server_response = http_get(server+"/api/user_stat_data",data);
	
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	return val;
}

/**
Deletes a post via CSAM nuke (any post can be deleted). Requires 4 admin privileges

@param postid The Id of the post
*/
void Ruqqus::admin_csam_nuke(std::string postid) {
	std::map<std::string,std::string> data;
	
	http_post(server+"/admin/csam_nuke/"+postid,data);
	return;
}

/**
Clears cache. Requires 3 admin privileges.
*/
void Ruqqus::admin_clear_cache() {
	Json::Value val;
	Json::Reader read;
	bool r;
	std::string server_response;
	
	std::map<std::string,std::string> data;
	
	server_response = http_get(server+"/admin/dump_cache",data);
	
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	std::string str = val["message"].asString();
	if(str.empty()) {
		throw std::runtime_error("Server trhrew invalid message (empty)");
	}
	
	return;
}
