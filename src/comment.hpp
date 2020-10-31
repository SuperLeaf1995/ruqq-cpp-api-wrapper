#ifndef COMMENT_HPP_INCLUDED
#define COMMENT_HPP_INCLUDED

class RuqqusComment {
	public:
		RuqqusUser author;
		std::string body;
		std::string body_html;
		int created_utc;
		int downvotes;
		int edited_utc;
		std::string fullname;
		std::string guild_name;
		std::string id;
		bool is_archived;
		bool is_banned;
		std::string ban_reason;
		bool is_deleted;
		bool is_nsfl;
		bool is_nsfw;
		bool is_offensive;
		int level;
		std::string parent;
		std::string permalink;
		std::string post;
		int score;
		std::string title;
		int upvotes;
};

#endif // COMMENT_HPP_INCLUDED
