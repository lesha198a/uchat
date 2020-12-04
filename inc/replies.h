#ifndef REPLIES_H
# define REPLIES_H

/*
** Error replies id following rfc 1459 used by our error manager
*/
# define ERR_NOSUCHNICK_ID            401
# define ERR_NOSUCHSERVER_ID        402
# define ERR_NOSUCHCHANNEL_ID        403
# define ERR_CANNOTSENDTOCHAN_ID    404
# define ERR_TOOMANYCHANNELS_ID        405
# define ERR_NORECIPIENT_ID            411
# define ERR_NOTEXTTOSEND_ID        412
# define ERR_UNKNOWNCOMMAND_ID        421

# define ERR_NONICKNAMEGIVEN_ID        431
# define ERR_ERRONEUSNICKNAME_ID    432
# define ERR_NICKNAMEINUSE_ID        433
# define ERR_NICKCOLLISION_ID        436

# define ERR_USERNOTINCHANNEL_ID    441
# define ERR_NOTONCHANNEL_ID        442
# define ERR_NOLOGIN_ID                444
# define ERR_NEEDMOREPARAMS_ID        461
# define ERR_CANTKILLSERVER_ID        483

# define ERR_TOPICTOOLONG_ID        499
# define ERR_ERRONEUSCHANNAME_ID    500

/*
** Error replies string following rfc 1459
*/
# define SRV_ERR_mask "srv;err;%s;\r\n"
# define SRV_RPL_mask "srv;rpl;%s;\r\n"
# define SRV_STT_mask "srv;stt;%s;\r\n"

# define SERVER_code "srv"
# define USER_code "usr"
# define REPLY_code "rpl"
# define ERROR_code "err"
# define NOTIFICATION_code "ntf"
# define STATUS_code "stt"

# define ERR_NOSUCHNICK            "no_such_nick"
# define ERR_NOSUCHSERVER        "no_such_server"
# define ERR_NOSUCHCHANNEL        "no_such_channel"
# define ERR_CANNOTSENDTOCHAN    "cannot_send_to_channel"
# define ERR_TOOMANYCHANNELS    "too_many_channels"

# define ERR_NORECIPIENT        "no_recipient"
# define ERR_NOTEXTTOSEND        "no_text_to_send"
# define ERR_UNKNOWNCOMMAND        "unknown_command"

# define ERR_NONICKNAMEGIVEN    "no_nick_is_given"
# define ERR_ERRONEUSNICKNAME    "invalid_nick"
# define ERR_ERRONEUSCHANNAME    "invalid_channel_name"
# define ERR_NICKNAMEINUSE        "nick_is_already_used"
# define ERR_NICKCOLLISION        "nick_collicion_kill"

# define ERR_USERNOTINCHANNEL    "user_is_not_in_channel"
# define ERR_NOTONCHANNEL        "you_are_not_in_that_channel"
# define ERR_NOLOGIN            "not_signed_in"
# define ERR_NEEDMOREPARAMS        "need_more_parameters"
# define ERR_CANTKILLSERVER        "you_cannot_kill_a_server"

/*
Normal replies
*/
# define RPL_LISTSTART_ID        321
# define RPL_LIST_ID            322
# define RPL_LISTEND_ID            323



# define RPL_LISTSTART            "[only for you] List of users:"
# define RPL_LIST                "srv;rpl;[only for you]  <%s> <%d>;\r\n"
# define RPL_ENDOFLIST            "[only for you] End of list."

# define RPL_TOPIC                "srv;rpl;Topic is %s;\r\n"
# define RPL_NOTOPIC            "No topic is set"

//use rpl mask # define RPL_NAMREPLY            "srv;rpl;<%s>\r\n"
# define RPL_ENDOFNAMES            "[only for you] End of /NAMES list."

//use rpl mask # define RPL_WHOREPLY            "srv;rpl;<%s>.;\r\n"
# define RPL_ENDOFWHO            "[only for you] End of /NAMES list."

/*
Custom replies
*/

# define ERR_TOOMANYARGUMENTS    "too_many_arguments"
# define ERR_ERRONEUSCHAR        "forbidden_character"
# define JOIN_NOTIF                "srv;ntf;%s has joined %s.;\r\n"
# define LEAVE_NOTIF            "srv;ntf;%s left channel.;\r\n"
# define LEAVE_CHAN                "left_channel"
# define MESSAGE_STR            "usr;rpl;%s;[only for you] %s;\r\n"
# define NICK_RESP                "srv;rpl;[only for you] Your nick is %s;\r\n"
# define NICK_NOTIF                "srv;rpl;%s is known as %s;\r\n"
# define QUIT_NOTIF                "srv;rpl;%s quit: %s;\r\n"
# define TOPIC_TOO_LONG            "[only for you] Topic too long"
# define RPL_WELCOME            "connected"
# define SIGN_BAD                 "bad_credentials"
# define SIGN_GOOD                "good_credentials"
# define CHANNEL_MSG               "usr;rpl;%s;%s;\r\n"

#endif
