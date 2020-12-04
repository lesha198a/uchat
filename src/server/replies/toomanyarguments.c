#include "../../../inc/server.h"

void err_toomanyarguments(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_ERR_mask, ERR_TOOMANYARGUMENTS);
	circular_send(user->socket, buf, len);
}
