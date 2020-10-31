#ifndef USER_HPP_INCLUDED
#define USER_HPP_INCLUDED

#include <string>
#include "title.hpp"

class RuqqusBadges {
	public:
		int created_utc;
		std::string name;
		std::string text;
		std::string url;
};

class RuqqusUser {
	public:
		std::vector<RuqqusBadges> badges;
		std::string banner_url;
		std::string bio;
		std::string bio_html;
		int comment_count;
		int comment_rep;
		int created_utc;
		std::string id;
		bool is_banned;
		std::string permalink;
		int post_count;
		int post_rep;
		std::string profile_url;
		RuqqusTitle title;
		std::string username;
};

#endif // USER_HPP_INCLUDED
