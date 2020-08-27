#ifndef GUILD_HPP_INCLUDED
#define GUILD_HPP_INCLUDED

class RuqqusGuild {
    public:
        std::string banner_url;
        std::string color;
        uintmax_t created_utc;
        std::string description;
        std::string description_html;
        std::string fullname;
        std::string id;
        bool is_banned;
        bool is_private;
        bool is_restricted;
        uintmax_t mods_count;
        std::string name;
        bool over_18;
        std::string permalink;
        std::string profile_url;
        uintmax_t subscriber_count;
};

#endif // GUILD_HPP_INCLUDED
