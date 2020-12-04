#include "../../../inc/server.h"

void	err_toomanychannels(t_users *user, char *chan_name)
{
	int		len;
	char	buf[MAX_INPUT_LEN + CRLF];

	len = snprintf(buf, MAX_INPUT_LEN + CRLF, SRV_ERR_mask, ERR_TOOMANYCHANNELS);
	circular_send(user->socket, buf, len);
}
