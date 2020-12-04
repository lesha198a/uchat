#include "../../../inc/server.h"

void err_nosuchchannel(t_users *user)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_ERR_mask, ERR_NOSUCHCHANNEL);
	circular_send(user->socket, buf, len);
}
