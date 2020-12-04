#include "../../../inc/server.h"

static void	gather_all_user_in_chan(t_channel *chan, t_users *user)
{
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	tmp = chan->users;
	while (tmp != NULL)
	{
        rpl_whoreply(user, tmp->user->nick.nick, buf);
		tmp = tmp->next;
	}
    rpl_endofwho(user, buf);
}

void		irc_who(t_server *server, t_users *user, char **command)
{
	t_channel	*chan;

	if (command[1] != NULL)
	{
		if (command[2] != NULL)
		{
            err_toomanyarguments(user);
			return ;
		}
		chan = channel_search(&server->channel, command[1]);
		if (chan == NULL)
		{
            err_nosuchchannel(user);
			return ;
		}
		gather_all_user_in_chan(chan, user);
		return ;
	}
    err_needmoreparams(user);
}
