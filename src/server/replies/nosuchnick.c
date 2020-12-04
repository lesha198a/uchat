#include "../../../inc/server.h"

void err_nosuchnick(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_ERR_mask, ERR_NOSUCHNICK);
	circular_send(user->socket, buf, len);
}
