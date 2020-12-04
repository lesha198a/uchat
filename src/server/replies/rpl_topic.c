#include "../../../inc/server.h"

void	rpl_topic(t_channel *chan, t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	memset(buf, 0x0, sizeof(buf));
	len = snprintf(buf, MAX_INPUT_LEN + CRLF, \
		RPL_TOPIC, chan->topic);
	circular_send(user->socket, buf, len);
}
