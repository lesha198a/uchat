#include "../../../inc/server.h"

void	rpl_list(t_channel *chan, t_users *user, char *buf)
{
	int len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, RPL_LIST, chan->name, chan->num);
	circular_send(user->socket, buf, len);
}
