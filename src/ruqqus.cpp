// std
#include <iostream>
#include <string>
#include <sstream>

// curlpp
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Types.hpp>

// json
#include <jsoncpp/json/json.h>

// ruqquscpp
#include "http.hpp"
#include "ruqqus.hpp"

/**
Converts JSON value to RuqqusGuild object

@param val Json value
*/
RuqqusGuild Ruqqus::JSON_to_guild(Json::Value val) {
	RuqqusGuild guild;
	guild.banner_url = val["banner_url"].asString();
	guild.color = val["color"].asString();
	guild.created_utc = val["created_utc"].asLargestUInt();
	guild.description = val["description"].asString();
	guild.description_html = val["description_html"].asString();
	guild.fullname = val["fullname"].asString();
	guild.id = val["id"].asString();
	guild.is_banned = val["is_banned"].asBool();
	guild.is_private = val["is_private"].asBool();
	guild.is_restricted = val["is_restricted"].asBool();
	guild.mods_count = val["mods_count"].asLargestUInt();
	guild.name = val["name"].asString();
	guild.over_18 = val["over_18"].asBool();
	guild.permalink = val["permalink"].asString();
	guild.profile_url = val["profile_url"].asString();
	guild.subscriber_count = val["subscriber_count"].asLargestUInt();
	return guild;
}

/**
Converts JSON value to RuqqusUser object

@param val Json value
*/
RuqqusUser Ruqqus::JSON_to_user(Json::Value val) {
	RuqqusUser user;
	user.banner_url = val["banner_url"].asString();
	user.bio = val["bio"].asString();
	user.bio_html = val["bio_html"].asString();
	user.comment_count = val["comment_count"].asLargestUInt();
	user.comment_rep = val["comment_rep"].asLargestUInt();
	user.created_utc = val["created_utc"].asLargestUInt();
	user.id = val["id"].asString();
	user.is_banned = val["is_banned"].asBool();
	user.permalink = val["permalink"].asString();
	user.post_count = val["post_count"].asLargestUInt();
	user.post_rep = val["post_rep"].asLargestUInt();
	user.profile_url = val["profile_url"].asString();
	user.username = val["username"].asString();
	for(Json::Value::ArrayIndex i = 0; i != val["badges"].size(); i++) {
		RuqqusBadges badge;

		badge.created_utc = val["badges"][i]["created_utc"].asLargestUInt();
		badge.name = val["badges"][i]["name"].asString();
		badge.text = val["badges"][i]["text"].asString();
		badge.url = val["badges"][i]["url"].asString();

		user.badges.push_back(badge);
	}
	user.badges.shrink_to_fit();
	user.title.color = val["title"]["color"].asString();
	user.title.id = val["title"]["id"].asLargestUInt();
	user.title.kind = val["title"]["kind"].asLargestUInt();
	user.title.text = val["title"]["text"].asString();
	return user;
}

/**
Converts JSON to RuqqusPost object

@param val Json value
*/
RuqqusPost Ruqqus::JSON_to_post(Json::Value val) {
	RuqqusPost post;
	post.author = val["author"].asString();
	post.body = val["body"].asString();
	post.body_html = val["body_html"].asString();
	post.comment_count = val["comment_count"].asLargestUInt();
	post.created_utc = val["created_utc"].asLargestUInt();
	post.domain = val["domain"].asString();
	post.downvotes = val["downvotes"].asLargestUInt();
	post.edited_utc = val["edited_utc"].asLargestUInt();
	post.embed_url = val["embed_url"].asString();
	post.fullname = val["fullname"].asString();
	post.guild_name = val["guild_name"].asString();
	post.id = val["id"].asString();
	post.is_archived = val["is_archived"].asBool();
	post.is_banned = val["is_banned"].asBool();
	post.is_deleted = val["is_deleted"].asBool();
	post.is_nsfl = val["is_nsfl"].asBool();
	post.is_nsfw = val["is_nsfw"].asBool();
	post.is_offensive = val["is_offensive"].asBool();
	post.original_guild_name = val["original_guild_name"].asString();
	post.permalink = val["permalink"].asString();
	post.score = val["score"].asLargestUInt();
	post.thumb_url = val["thumb_url"].asString();
	post.title = val["title"].asString();
	post.upvotes = val["upvotes"].asLargestUInt();
	post.url = val["url"].asString();
	post.author_title.color = val["author_title"]["color"].asString();
	post.author_title.id = val["author_title"]["id"].asLargestUInt();
	post.author_title.kind = val["author_title"]["kind"].asLargestUInt();
	post.author_title.text = val["author_title"]["text"].asString();
	return post;
}

/**
Converts comment to RuqqusComment

@param val Json value
*/
RuqqusComment Ruqqus::JSON_to_comment(Json::Value val) {
	RuqqusComment comment;
	comment.author = val["author"].asString();
	comment.body = val["body"].asString();
	comment.body_html = val["body_html"].asString();
	comment.created_utc = val["created_utc"].asLargestUInt();
	comment.downvotes = val["downvotes"].asLargestUInt();
	comment.edited_utc = val["edited_utc"].asLargestUInt();
	comment.fullname = val["fullname"].asString();
	comment.guild_name = val["guild_name"].asString();
	comment.id = val["id"].asString();
	comment.is_archived = val["is_archived"].asBool();
	comment.is_banned = val["is_banned"].asBool();
	comment.is_deleted = val["is_deleted"].asBool();
	comment.is_nsfl = val["is_nsfl"].asBool();
	comment.is_nsfw = val["is_nsfw"].asBool();
	comment.is_offensive = val["is_offensive"].asBool();
	comment.level = val["level"].asLargestUInt();
	comment.parent = val["parent"].asString();
	comment.permalink = val["permalink"].asString();
	comment.post = val["post"].asString();
	comment.score = val["score"].asLargestUInt();
	comment.title = val["title"].asString();
	comment.upvotes = val["upvotes"].asLargestUInt();
	return comment;
}

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
Obtains information about username and returns a RuqqusUser class

@param username The name of the user to obtain information from it
*/
RuqqusUser Ruqqus::user_info(std::string username) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_get(server+"/api/v1/user/"+username);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	return JSON_to_user(val);
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

	server_response = http_get(server+"/api/v1/pid/"+postid);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return JSON_to_post(val);
}

/**
Obtains information about the comment and returns a RuqqusComment class

@param commentid The Id of the comment to get information from it
*/
RuqqusComment Ruqqus::comment_info(std::string commentid) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_get(server+"/api/v1/cid/"+commentid);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return JSON_to_comment(val);
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

	server_response = http_get(server+"/api/board_available/"+guildname);
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

/**
Gets listing of posts in guildname

@param guildname The name of the guild to get listing from
*/
std::vector<RuqqusPost> Ruqqus::guild_listing(std::string guildname) {
	Json::Value val;
	Json::Reader read;
	std::string server_response;
	bool r;

	server_response = http_post(server+"/api/v1/guild/"+guildname+"/listing");
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	std::vector<RuqqusPost> ret;
	for(Json::Value::ArrayIndex i = 0; i != val["api"].size(); i++) {
		RuqqusPost post;
		post = JSON_to_post(val["api"][i]);
		ret.push_back(post);
	}
	return ret;
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

	server_response = http_get(server+"/api/is_available/"+username);
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}

	return val[username].asBool();
}

/**
Follows a user

@param username The username of the user
*/
void Ruqqus::user_follow(std::string username) {
	http_post(server+"/api/follow/"+username);
	return;
}

/**
Unfollows a user

@param username The username of the user
*/
void Ruqqus::user_unfollow(std::string username) {
	http_post(server+"/api/unfollow/"+username);
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
	
	server_response = http_post(server+"/mod/exile/"+bid,"username="+username);

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

/**
Submits a post
*/
bool Ruqqus::post_submit(std::string url, std::string title, std::string body, std::string guildname) {
	// Almost all parts are needed except for URL
	http_post(server+"/api/v1/submit","url="+url+"&title="+title+"&body="+body+"&board="+guildname);
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
	
	// Do not confuse by the name, submit actually obtains the
	// post title via the id
	server_response = http_get(server+"/api/submit/title?url="+postid);
	
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
	http_post_http_response(server+"/delete_post/"+postid);
	return;
}

/**
Toggles a post to NSFW

@param postid The Id of the post
*/
void Ruqqus::post_toggle_nsfw(std::string postid) {
	http_post_http_response(server+"/api/toggle_post_nsfw/"+postid);
	return;
}

/**
Toggles a post to NSFL

@param postid The Id of the post
*/
void Ruqqus::post_toggle_nsfl(std::string postid) {
	http_post_http_response(server+"/api/toggle_post_nsfl/"+postid);
	return;
}

/**
Votes for a post

@param postid The Id of the post
*/
void Ruqqus::post_vote(std::string postid, signed char v) {
	http_post_http_response(server+"/api/vote/post/"+postid+"/"+std::to_string(v));
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
	http_post_http_response(server+"/api/flag/post/"+postid,"report_type="+report_type);
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
	http_post(server+"/api/vote/comment/"+cid+"/"+std::to_string(v));
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
	http_post(server+"/api/ban_user/"+uid,"reason="+reason+"&message="+message+"&days="+std::to_string(days));
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

	http_post(server+"/api/unban_user/"+uid,"alts="+alt);
	return;
}

/**
Bans a post. Requires 3 admin privileges

@param pid The Id of the post
@param reason Reason for ban
*/
void Ruqqus::admin_ban_post(std::string pid, std::string reason) {
	http_post(server+"/api/ban_post/"+pid,"?reason="+reason);
	return;
}

/**
Unbans a post. Requires 3 admin privileges

@param pid The Id of the post
*/
void Ruqqus::admin_unban_post(std::string pid) {
	http_post(server+"/api/unban_post/"+pid);
	return;
}

/**
Makes a post sticky. Requires 3 admin privileges

@param pid The Id of the post
*/
void Ruqqus::admin_sticky_post(std::string pid) {
	http_post(server+"/api/sticky_post/"+pid);
	return;
}

/**
Bans a comment. Requires 4 admin privileges

@param cid The Id of the comment
*/
void Ruqqus::admin_ban_comment(std::string cid) {
	http_post(server+"/api/ban_comment/"+cid);
	return;
}

/**
Unbans a comment. Requires 4 admin privileges

@param cid The Id of the comment
*/
void Ruqqus::admin_unban_comment(std::string cid) {
	http_post(server+"/api/unban_guild/"+cid);
	return;
}

/**
Bans a guild. Requires 4 admin privileges

@param bid The Id of the board
@param reason Reason for ban
*/
void Ruqqus::admin_ban_guild(std::string bid, std::string reason) {
	http_post(server+"/api/ban_guild/"+bid+"?reason="+reason);
	return;
}

/**
Unbans a guild. Requires 4 admin privileges

@param bid The Id of the board
*/
void Ruqqus::admin_unban_guild(std::string bid) {
	http_post(server+"/api/unban_guild/"+bid);
	return;
}

/**
Becomes mod of the board automatically. Requires 4 admin privileges

@param bid The Id of the board
*/
void Ruqqus::admin_mod_self(std::string bid) {
	http_post(server+"/api/mod_self/"+bid);
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
	
	server_response = http_get(server+"/api/user_stat_data?days="+std::to_string(days));
	
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
	http_post(server+"/admin/csam_nuke/"+postid);
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
	
	server_response = http_get(server+"/admin/dump_cache");
	
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

/**
Generates a new token with OAuth. Token is returned as a std::string.

@param client_id
@param client_secret
@param refresh_token
*/
std::string Ruqqus::oauth_update_token(void) {
	Json::Value val;
	Json::Reader read;
	bool r;
	std::string server_response;
	
	server_response = http_post(server+"/oauth/grant","client_id="+client_id+"&client_secret="+client_secret+"&refresh_token="+refresh_token+"&grant_type=refresh");
	
	r = read.parse(server_response,val,false);
	if(!r) {
		throw std::runtime_error("Cannot parse JSON value");
	}
	
	std::string token = val["access_token"].asString();
	if(token.empty()) {
		throw std::runtime_error("Server threw invalid message");
	}

	http_set_oauth_token(token);
	
	return token;
}

/**
Ruqqus constructor

@param servername The name of the server where the API should be contacted at, very useful to set it to localhost in case of tests
*/
Ruqqus::Ruqqus(std::string servername) {
	curlpp::initialize();
	curlpp::Cleanup raii_cleanup;
	
	server = servername;
}


/**
Ruqqus deconstructor. Dies.
*/
Ruqqus::~Ruqqus() {
	auto_token_continue = false;
	curlpp::terminate();
}
