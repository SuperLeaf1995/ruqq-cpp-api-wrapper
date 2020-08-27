#ifndef POST_HPP_INCLUDED
#define POST_HPP_INCLUDED

class RuqqusPost {
    public:
        std::string author;
        RuqqusTitle author_title;
        std::string body;
        std::string body_html;
        uintmax_t comment_count;
        uintmax_t created_utc;
        std::string domain;
        uintmax_t downvotes;
        uintmax_t edited_utc;
        std::string embed_url;
        std::string fullname;
        std::string guild_name;
        std::string id;
        bool is_archived;
        bool is_banned;
        bool is_deleted;
        bool is_nsfl;
        bool is_nsfw;
        bool is_offensive;
        std::string original_guild_name;
        std::string permalink;
        uintmax_t score;
        std::string thumb_url;
        std::string title;
        uintmax_t upvotes;
        std::string url;
};

#endif // COMMENT_HPP_INCLUDED
