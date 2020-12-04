#include "../../inc/server.h"

t_command g_func[] =
{
	{ "/help", 5, irc_help },
	{ "/nick", 5, irc_nick },
	{ "/list", 5, irc_list },
	{ "/join", 5, irc_join },
	{ "/leave", 6, irc_leave },
	{ "/topic", 6, irc_topic },
	{ "/who", 4, irc_who },
	{ "/msg", 4, irc_msg },
	{ "/quit", 5, irc_quit },
    {"/signin", 7, irc_signin},
    {"/signup", 7, irc_signup},
	{ "/kill", 5, irc_kill },
    {"/gethistory", 11, irc_gethistory},

};

static bool	handle_command(t_server *server, t_users *user, char **command)
{
	int		len;
	int		count;
	int		cmp_len;
	int		func_num;

	count = 0;
	len = ft_strlen(command[0]);
	func_num = sizeof(g_func) / sizeof(g_func[0]);
	while (count < func_num)
	{
		cmp_len = len > g_func[count].name_len ? len : g_func[count].name_len;
		if (ft_strncmp(g_func[count].name, command[0], cmp_len) == 0)
		{
			((t_func*)g_func[count].func)(server, user, command);
			return (true);
		}
		count++;
	}
	if (FD_ISSET(user->socket, &server->info.write))
        err_unknow_command(user);
	return (false);
}

static void	handle_message(t_server *server, t_users *user, char *final)
{
	int				len;
	char			to_send[MAX_INPUT_LEN + CRLF];
	t_channel_user	*usr_list;

	ft_memset(to_send, 0x0, MAX_INPUT_LEN + CRLF);
	usr_list = ((t_channel*)user->chan)->users;
	if (usr_list == NULL)
		return ;
    db_addmessage(((t_channel*)user->chan)->name,user->nick.nick,final);
	len = snprintf(to_send, MAX_INPUT_LEN + CRLF, CHANNEL_MSG, user->nick.nick, final);
	while (usr_list != NULL)
	{
		if (FD_ISSET(usr_list->user->socket, &server->info.write))
			circular_send(usr_list->user->socket, to_send, len);
		usr_list = usr_list->next;
	}
}

bool		check_command(char *command, int size)
{
	int count;

	count = 0;
	while (count < size)
	{
		if (command[count] == '\t' || command[count] == '\n' || \
			command[count] == '\v' || command[count] == '\f' || \
			command[count] == '\r')
			return (false);
		count++;
	}
	return (true);
}

void		interpreter(t_server *server, t_users *user)
{
	char	*cmd[3];
	char	extracted[MAX_INPUT_LEN];

	ft_memset(cmd, 0x0, sizeof(char*) * 3);
	extract_and_update(&user->read, extracted);
	if (check_command(extracted, ft_strlen(extracted)) == false)
	{
		err_erroneuschar(user);
		return ;
	}
	if (extracted[0] == '/')
	{
		if (command_split(cmd, extracted) != true)
			return ;
		handle_command(server, user, cmd);
		command_free(cmd);
	}
	else if (user->chan != NULL && FD_ISSET(user->socket, &server->info.write))
		handle_message(server, user, extracted);
}
