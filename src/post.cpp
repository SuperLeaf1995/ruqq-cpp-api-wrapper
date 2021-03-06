// std
#include <iostream>
#include <string>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/**
Submits a post
*/
bool Ruqqus::post_submit(std::string url, std::string title, std::string body, std::string guildname) {
	std::map<std::string,std::string> form;

	form.insert(std::pair<std::string,std::string>("url",url));
	form.insert(std::pair<std::string,std::string>("title",title));
	form.insert(std::pair<std::string,std::string>("body",body));
	form.insert(std::pair<std::string,std::string>("board",guildname));
	
	// Almost all parts are needed except for URL
	http_form_post(server+"/api/v1/submit",form);
	return true;
}

/**
Gets a post title

@param postid The Id of the post
@return Title of the post
*/
std::string Ruqqus::post_get_title(std::string postid) {
	Json::Value val;
	Json::Reader read;
	bool r;
	std::string server_response;
	
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("url",postid));
	
	// Do not confuse by the name, submit actually obtains the
	// post title via the id
	server_response = http_get(server+"/api/submit/title",data);
	
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	std::string str = val["error"].asString();
	if(str.empty()) {
		throw std::runtime_error("Server trhew error");
	}
	
	return val["title"].asString();
}

/**
Deletes a post

@param postid The Id of the post
*/
void Ruqqus::post_delete(std::string postid) {
	std::map<std::string,std::string> data;
	http_post(server+"/delete_post/"+postid,data);
	return;
}

/**
Toggles a post to NSFW

@param postid The Id of the post
*/
void Ruqqus::post_toggle_nsfw(std::string postid) {
	std::map<std::string,std::string> data;
	http_post(server+"/api/v1/toggle_post_nsfw/"+postid,data);
	return;
}

/**
Toggles a post to NSFL

@param postid The Id of the post
*/
void Ruqqus::post_toggle_nsfl(std::string postid) {
	std::map<std::string,std::string> data;
	http_post(server+"/api/v1/toggle_post_nsfl/"+postid,data);
	return;
}

/**
Votes for a post

@param postid The Id of the post
*/
void Ruqqus::post_vote(std::string postid, signed char v) {
	/* v1 dosen't uses cookies like the other one wich dosen't has the v1 */
	std::map<std::string,std::string> data;
	http_post(server+"/api/v1/vote/post/"+postid+"/"+std::to_string(v),data);
	return;
}

/**
Flags/reports a post

@param postid The Id of the post
*/
void Ruqqus::post_flag(std::string postid, std::string report_type) {
	// There are two types of flagging, admin wich does "flagging"
	// and "guild", wich reports the post to the guildmaster
	//
	// If you are making a moderation bot, you should use "guild" type
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("report_type",report_type));
	http_post(server+"/api/flag/post/"+postid,data);
	return;
}

/**
Gets post listing
*/
std::vector<RuqqusPost> Ruqqus::front_listing_post(std::string sort, std::string limit, std::string page) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	
	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("sort",sort));
	data.insert(std::pair<std::string,std::string>("limit",limit));
	data.insert(std::pair<std::string,std::string>("page",page));
	
	server_response = http_get(server+"/api/v1/front/listing",data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::vector<RuqqusPost> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["data"].size(); i++) {
		RuqqusPost post;
		post = JSON_to_post(val["data"][i]);
		ret.push_back(post);
	}
	return ret;
}

/**
Gets post listing
*/
std::vector<RuqqusPost> Ruqqus::all_listing_post(std::string sort, std::string limit, std::string page) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("sort",sort));
	data.insert(std::pair<std::string,std::string>("limit",limit));
	data.insert(std::pair<std::string,std::string>("page",page));
	
	server_response = http_get(server+"/api/v1/all/listing",data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::vector<RuqqusPost> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["data"].size(); i++) {
		RuqqusPost post;
		post = JSON_to_post(val["data"][i]);
		ret.push_back(post);
	}
	return ret;
}

/**
Gets listing of posts in guildname

@param guildname The name of the guild to get listing from
*/
std::vector<RuqqusPost> Ruqqus::guild_listing_post(std::string guildname, std::string sort, std::string limit, std::string page) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	std::map<std::string,std::string> data;
	data.insert(std::pair<std::string,std::string>("sort",sort));
	data.insert(std::pair<std::string,std::string>("limit",limit));
	data.insert(std::pair<std::string,std::string>("page",page));

	server_response = http_get(server+"/api/v1/guild/"+guildname+"/listing",data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::vector<RuqqusPost> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["data"].size(); i--) {
		RuqqusPost post;
		post = JSON_to_post(val["data"][i]);
		ret.push_back(post);
	}
	return ret;
}

/**
Obtains information about the post and returns a RuqqusPost class

@param postid The Id of the post to get information from it
*/
RuqqusPost Ruqqus::post_info(std::string postid) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;
	
	std::map<std::string,std::string> data;

	server_response = http_get(server+"/api/v1/post/"+postid,data);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return JSON_to_post(val);
}
