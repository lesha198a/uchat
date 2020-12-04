#include "../../../inc/server.h"

void	rpl_welcome(t_users *user)
{
	int		len;
	char	data[MAX_INPUT_LEN + CRLF];

	len = snprintf(data, MAX_INPUT_LEN + CRLF, SRV_RPL_mask, RPL_WELCOME);
	circular_send(user->socket, data, len);
}
