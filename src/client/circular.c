

#include "../../inc/client.h"

void	extract_and_update(t_circular *circ, char *final)
{
	int count;
	int next;

	count = 0;
	while (count < circ->len)
	{
		next = (circ->head + 1) % MAX_INPUT_LEN;
		if (circ->buf[circ->head] == 0xd && circ->buf[next] == 0xa)
		{
			circ->head = (circ->head + CRLF) % MAX_INPUT_LEN;
			circ->len -= (count + CRLF);
			break ;
		}
		final[count] = circ->buf[circ->head];
		circ->head = next;
		count++;
	}
	final[count] = '\0';
}

bool	search_for_crlf(char *buf, int head, int size)
{
	int next;

	while (size)
	{
		next = (head + 1) % MAX_INPUT_LEN;
		if (buf[head] == 0xd && buf[next] == 0xa)
			return (true);
		head = next;
		size--;
	}
	return (false);
}

void	circular_push(t_circular *circ, char *received, int size)
{
	while (size)
	{
		circ->buf[circ->tail] = *received++;
		circ->tail = (circ->tail + 1) % MAX_INPUT_LEN;
		size--;
	}
}

bool circular_get(t_user *user)
{
	int				ret;
	unsigned char	data[MAX_INPUT_LEN + CRLF];
	unsigned char	decrypted[MAX_INPUT_LEN + CRLF];

	ft_memset(data, 0x0, sizeof(data));
	ft_memset(decrypted, 0x0, sizeof(decrypted));
	ret = recv(user->socket, data, (MAX_INPUT_LEN + CRLF) - user->read.len, 0);
	if (ret < 1)
	{
	    //todo check it
		//refresh_top_interface(inter, "Can't receive data from server");
		return (false);
	}
	rc4_decrypt(SECRET_KEY, data, decrypted, ret);
	circular_push(&user->read, (char*)decrypted, ret);
	user->read.len += ret;
	return (true);
}

void circular_send(t_user *user)
{
	uint8_t encrypted[MAX_INPUT_LEN + CRLF];

	rc4_encrypt(SECRET_KEY, (unsigned char*)user->input, encrypted, (int)strlen(user->input));
	if (send(user->socket, encrypted, (int)strlen(user->input), 0) < 0)
	{
		//refresh_top_interface(inter, "Can't send data to server.");
		//todo check it
		return ;
	}
	usleep(50);
}
