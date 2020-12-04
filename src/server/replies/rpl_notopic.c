#include "../../../inc/server.h"

void rpl_notopic(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_RPL_mask, RPL_NOTOPIC);
	circular_send(user->socket, buf, len);
}
