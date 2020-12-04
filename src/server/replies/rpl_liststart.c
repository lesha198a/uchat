#include "../../../inc/server.h"

void	rpl_liststart(t_users *user, char *buf)
{
	int len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_RPL_mask, RPL_LISTSTART);
	circular_send(user->socket, buf, len);
}
