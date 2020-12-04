#include "../../../inc/server.h"

void	irc_help(t_server *server, t_users *user, char **command)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	(void)server;
	(void)command;
	len = snprintf(buf, MAX_INPUT_LEN + CRLF, \
		"srv;rpl;/help                : print this help;\r\n"		\
		"srv;rpl;/nick <name>         : change username;\r\n"		\
		"srv;rpl;/list [chan]         : list channel;\r\n"			\
		"srv;rpl;/join <chan>         : join channel;\r\n"			\
		"srv;rpl;/leave <chan>        : leave channel;\r\n"			\
		"srv;rpl;/topic <chan [topic]>: show/set topic;\r\n"			\
		"srv;rpl;/who [chan]          : list connected user;\r\n"	\
		"srv;rpl;/msg <usr> <message> : send message to user;\r\n"	\
		"srv;rpl;/connect <ip [port]> : connect to server;\r\n"		\
		"srv;rpl;/quit                : quit irc;\r\n"				\
		"srv;rpl;/kill [passwd]       : shutdown connected server;\r\n");
	if (FD_ISSET(user->socket, &server->info.write))
		circular_send(user->socket, buf, len);
}
