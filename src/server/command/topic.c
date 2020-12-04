#include "../../../inc/server.h"

static void	send_channel_topic(t_channel *chan, t_users *user)
{
	if (chan->topic[0] == '\0')
        rpl_notopic(user);
	else
		rpl_topic(chan, user);
}

static void	notify_topic_change(t_channel *chan, t_users *user, char *old_top)
{
	int				len;
	char			buf[MAX_INPUT_LEN + CRLF];
	t_channel_user	*tmp;

	tmp = chan->users;
	len = snprintf(buf, MAX_INPUT_LEN + CRLF, \
		"srv;rpl;%s changed topic from '%s' to '%s';\r\n", \
		user->nick.nick, old_top, chan->topic);
	while (tmp != NULL)
	{
		circular_send(tmp->user->socket, buf, len);
		tmp = tmp->next;
	}
}

static void	modify_channel_topic(t_channel *chan, t_users *user, char *new_top)
{
	int		size;
	char	old_top[MAX_TOPIC_LEN + 1];

	size = ft_strlen(new_top);
	if (size > MAX_TOPIC_LEN)
	{
        err_topictoolong(user);
		return ;
	}
	ft_memset(old_top, 0x0, MAX_TOPIC_LEN + 1);
	ft_memcpy(old_top, chan->topic, ft_strlen(chan->topic));
	ft_memset(chan->topic, 0x0, MAX_TOPIC_LEN);
	ft_memcpy(chan->topic, new_top, size);
	notify_topic_change(chan, user, old_top);
}

void		irc_topic(t_server *server, t_users *user, char **command)
{
	t_channel *chan;

	if (command[1] != NULL)
	{
		chan = channel_search(&server->channel, command[1]);
		if (chan == NULL)
		{
            err_nosuchchannel(user);
			return ;
		}
		if (command[2] == NULL)
		{
			send_channel_topic(chan, user);
			return ;
		}
		if (user->chan != chan)
		{
            err_notonchannel(user);
			return ;
		}
		modify_channel_topic(chan, user, command[2]);
		return ;
	}
    err_needmoreparams(user);
}
