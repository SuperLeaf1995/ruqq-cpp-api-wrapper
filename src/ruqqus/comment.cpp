// std
#include <iostream>
#include <string>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/**
Obtains information about the comment and returns a RuqqusComment class

@param commentid The Id of the comment to get information from it
*/
RuqqusComment Ruqqus::comment_info(std::string commentid) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_get(server+"/api/v1/comment/"+commentid);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return JSON_to_comment(val);
}

/**
Does a comment

@param pid Post ID
*/
void Ruqqus::comment_submit(std::string pid, std::string body) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	std::map<std::string,std::string> form;

	form.insert(std::pair<std::string,std::string>("parent_fullname","t2_"+pid));
	form.insert(std::pair<std::string,std::string>("submission",pid));
	form.insert(std::pair<std::string,std::string>("body",body));

	server_response = http_form_post(server+"/api/v1/comment",form);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::string err = val["error"].asString();
	if(!err.empty()) {
		throw std::runtime_error("Server returned error "+err);
	}
	return;
}

/**
Does a reply to a comment in a post

@param pid Post ID
@param cid Comment ID
*/
void Ruqqus::comment_reply(std::string pid, std::string cid, std::string body) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	std::map<std::string,std::string> form;

	form.insert(std::pair<std::string,std::string>("parent_fullname","t3_"+cid));
	form.insert(std::pair<std::string,std::string>("submission",pid));
	form.insert(std::pair<std::string,std::string>("body",body));

	server_response = http_form_post(server+"/api/v1/comment",form);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::string err = val["error"].asString();
	if(!err.empty()) {
		throw std::runtime_error("Server returned error "+err);
	}
	return;
}

/**
Get a comment in post

@param pid Id of the post
@param cid Id of the comment IN post
*/
RuqqusComment Ruqqus::comment_get_in_post(std::string pid, std::string cid) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_get(server+"/api/v1/post/"+pid+"/comment/"+cid);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	return JSON_to_comment(val);
}

/**
Votes for a comment

@param cid The Id of the comment
*/
void Ruqqus::comment_vote(std::string cid, signed char v) {
	/* v1 dosen't uses cookies like the other one wich dosen't has the v1 */
	http_post(server+"/api/v1/vote/comment/"+cid+"/"+std::to_string(v));
	return;
}

/**
Flags a comment

@param cid The Id of the comment
*/
void Ruqqus::comment_flag(std::string cid) {
	http_post_http_response(server+"/api/flag/comment/"+cid);
	return;
}

/**
Gets comment listing
*/
std::vector<RuqqusComment> Ruqqus::all_listing_comment(void) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	
	server_response = http_get(server+"/api/v1/front/comments");
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	std::vector<RuqqusComment> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["data"].size(); i++) {
		RuqqusComment com;
		com = JSON_to_comment(val["data"][i]);
		ret.push_back(com);
	}
	return ret;
}

/**
Gets listing of comments in guild

@param guildname The name of the guild to get listing from
*/
std::vector<RuqqusComment> Ruqqus::guild_listing_comment(std::string guildname) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_get(server+"/api/v1/guild/"+guildname+"/comments");
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::vector<RuqqusComment> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["data"].size(); i--) {
		RuqqusComment com;
		com = JSON_to_comment(val["data"][i]);
		ret.push_back(com);
	}
	return ret;
}
