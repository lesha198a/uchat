#include "../../../inc/server.h"

void rpl_endofwho(t_users *user, char *buf)
{
	int len;

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_RPL_mask, RPL_ENDOFWHO);
	circular_send(user->socket, buf, len);
}
