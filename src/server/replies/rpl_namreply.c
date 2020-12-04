#include "../../../inc/server.h"

void rpl_namreply(t_users *user, char *nick, char *buf)
{
	int	len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_RPL_mask, nick);
	circular_send(user->socket, buf, len);
}
