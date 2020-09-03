#ifndef RUQQUS_HPP_INCLUDED
#define RUQQUS_HPP_INCLUDED

#include <string>
#include <vector>

#include "guild.hpp"
#include "user.hpp"
#include "post.hpp"
#include "comment.hpp"

class Ruqqus {
	public:
		bool auto_token_continue;
	
		// internals
		std::string server;
		std::string token;
		std::string client_id;
		std::string client_secret;
		std::string refresh_token;
		
		// internal functions to make life easier(TM)
		RuqqusGuild JSON_to_guild(Json::Value val);
		RuqqusUser JSON_to_user(Json::Value val);
		RuqqusPost JSON_to_post(Json::Value val);
		RuqqusComment JSON_to_comment(Json::Value val);
		
		// official API functions
		RuqqusGuild guild_info(std::string guildname);
		RuqqusUser user_me(void);
		RuqqusUser user_info(std::string username);
		RuqqusPost post_info(std::string post);
		RuqqusComment comment_info(std::string comment);

		// guild
		bool guild_available(std::string guildname);
		bool guild_join(std::string guildname);
		bool guild_leave(std::string guildname);
		std::vector<RuqqusPost> guild_listing_post(std::string guildname, std::string sort = "new");
		std::vector<RuqqusComment> guild_listing_comment(std::string guildname);
		
		// user
		bool user_available(std::string username);
		void user_follow(std::string username);
		void user_unfollow(std::string username);
		void user_exile(std::string username, std::string bid);
		std::vector<RuqqusPost> user_listing_post(std::string username, std::string sort = "new");
		
		// post
		bool post_submit(std::string url, std::string title, std::string body, std::string guildname);
		std::string post_get_title(std::string postid);
		void post_toggle_nsfw(std::string postid);
		void post_delete(std::string postid);
		void post_toggle_nsfl(std::string postid);
		void post_vote(std::string postid, signed char v);
		void post_flag(std::string postid, std::string report_type);
		std::vector<RuqqusPost> post_listing(std::string sort);
		
		// comment
		RuqqusComment comment_get_in_post(std::string pid, std::string cid);
		void comment_vote(std::string cid, signed char v);
		void comment_flag(std::string cid);
		void comment_submit(std::string pid, std::string body);
		void comment_reply(std::string pid, std::string cid, std::string body);
		
		// administrative functions (req. cookie)
		void admin_ban_user(std::string uid, int days, std::string reason, std::string message);
		void admin_unban_user(std::string uid, bool unban_alts = true);
		void admin_ban_post(std::string pid, std::string reason);
		void admin_unban_post(std::string pid);
		void admin_sticky_post(std::string pid);
		void admin_ban_comment(std::string cid);
		void admin_unban_comment(std::string cid);
		void admin_ban_guild(std::string bid, std::string reason);
		void admin_unban_guild(std::string bid);
		void admin_mod_self(std::string bid);
		Json::Value admin_user_stat(int days);
		void admin_csam_nuke(std::string postid);
		void admin_clear_cache();
		
		// The auto-token updater, so you don't have to worry about expiring tokens ;)
		std::string oauth_update_token(void);
		std::string oauth_auto_update_token(void);

		Ruqqus(std::string servername);
		~Ruqqus();
};

#endif // RUQQUS_HPP_INCLUDED
