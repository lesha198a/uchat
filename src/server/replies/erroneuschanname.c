#include "../../../inc/server.h"

void	err_erroneuschanname(t_users *user, char *name)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_ERR_mask, ERR_ERRONEUSCHANNAME);
	circular_send(user->socket, buf, len);
}
