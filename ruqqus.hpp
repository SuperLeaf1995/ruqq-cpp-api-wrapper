#ifndef RUQQUS_HPP_INCLUDED
#define RUQQUS_HPP_INCLUDED

#include "guild.hpp"
#include "user.hpp"
#include "post.hpp"
#include "comment.hpp"

class Ruqqus {
    private:
        std::string server;
    public:
        RuqqusGuild guild_info(std::string guildname);
        RuqqusUser user_info(std::string username);
        RuqqusPost post_info(std::string post);
        RuqqusComment comment_info(std::string comment);

        bool guild_available(std::string guildname);
        bool join_guild(std::string guildname);

        Ruqqus(std::string servername);
        ~Ruqqus();
};

#endif // RUQQUS_HPP_INCLUDED
