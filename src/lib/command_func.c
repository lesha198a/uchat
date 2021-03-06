
#include "../../inc/lib.h"

int		command_size(char *command)
{
	int i;

	i = 0;
	while (command[i] != '\0' && ft_isspace(command[i]) == false)
		i++;
	return (i);
}

void	command_free(char **command)
{
	if (command[0] != NULL)
	{
		free(command[0]);
		if (command[1] != NULL)
		{
			free(command[1]);
			if (command[2] != NULL)
				free(command[2]);
		}
	}
}

bool	command_split(char **command, const char *final)
{
	int		size;
	char	*ptr;

	ptr = (char*)final;
	if ((size = command_size(ptr)) > 0)
	{
		if (!(command[0] = ft_strndup(ptr, size)))
			return (false);
		ptr = ptr + (size + 1);
		if ((size = command_size(ptr)) > 0)
		{
			if (!(command[1] = ft_strndup(ptr, size)))
				return (false);
			ptr = ptr + (size + 1);
			if ((size = ft_strlen(ptr)) > 0)
			{
				if (!(command[2] = ft_strndup(ptr, size)))
					return (false);
			}
		}
		return (true);
	}
	return (false);
}
