#ifndef COMMENT_HPP_INCLUDED
#define COMMENT_HPP_INCLUDED

class RuqqusComment {
    public:
        std::string author;
        std::string body;
        std::string body_html;
        uintmax_t created_utc;
        uintmax_t downvotes;
        uintmax_t edited_utc;
        std::string fullname;
        std::string guild_name;
        std::string id;
        bool is_archived;
        bool is_banned;
        bool is_deleted;
        bool is_nsfl;
        bool is_nsfw;
        bool is_offensive;
        uintmax_t level;
        std::string parent;
        std::string permalink;
        std::string post;
        uintmax_t score;
        std::string title;
        uintmax_t upvotes;
};

#endif // COMMENT_HPP_INCLUDED
