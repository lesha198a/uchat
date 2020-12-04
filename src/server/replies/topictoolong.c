#include "../../../inc/server.h"

void err_topictoolong(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_RPL_mask, TOPIC_TOO_LONG);
	circular_send(user->socket, buf, len);
}
