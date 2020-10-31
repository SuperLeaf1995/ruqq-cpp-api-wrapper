#ifndef GUILD_HPP_INCLUDED
#define GUILD_HPP_INCLUDED

class RuqqusGuild {
	public:
		std::string banner_url;
		std::string color;
		int created_utc;
		std::string description;
		std::string description_html;
		std::string fullname;
		std::string id;
		bool is_banned;
		bool is_private;
		bool is_restricted;
		int mods_count;
		std::string name;
		bool over_18;
		std::string permalink;
		std::string profile_url;
		int subscriber_count;
};

#endif // GUILD_HPP_INCLUDED
