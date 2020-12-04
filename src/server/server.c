#include "../../inc/server.h"

static void	zeroed(t_server *server)
{
	server->sock = 0;
	ft_memset(&server->info, 0x0, sizeof(t_fd));
	ft_memset(server->kill_pass, 0x0, KILL_PASS_LEN + 1);
	server->users = NULL;
	server->channel = NULL;
}

static bool	is_valid_argument(const char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] < '0' || str[count] > '9')
		{
			//printf("Error: '%s' port is invalid. Abort\n", str);
			return (false);
		}
		count++;
	}
	return (true);
}

static bool	launcher(t_server *server, char *port)
{
	if (is_valid_argument(port) != true)
		return (false);
	if (initialize(server, port) != true)
		return (false);
	if (running(server) != true)
		return (false);
	return (true);
}

int mmmmain(int ac, char **av)
{
	t_server server;
    if (!db_init())
        return 1;
	zeroed(&server);
	if (ac == 1)
	{
		//printf("[LOG !] No port provided, using default '%s'\n", DEFAULT_PORT);
		if (launcher(&server, DEFAULT_PORT) != true)
			return (ERROR);
	}
	else if (ac == 2)
	{
		if (launcher(&server, av[1]) != true)
			return (ERROR);
	}
	else
	{
		//printf("Usage: %s <port>\n", av[0]);
		return (ERROR);
	}
	return (ERROR);
}

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        write(2, "usage: ./uchat_server [port]", strlen("usage: ./uchat_server [port])"));
        exit(0);
    }

    pid_t process_id = 0;
    pid_t sid = 0;
    // Create child process
    process_id = fork();
    // Indication of fork() failure
    if (process_id < 0)
    {
        printf("fork failed!\n");
        // Return failure in exit status
        exit(1);
    }
    // PARENT PROCESS. Need to kill it.
    if (process_id > 0)
    {
        printf("process_id of child process %d \n", process_id);
        // return success in exit status
        exit(0);
    }

    umask(0);
    sid = setsid();
    if(sid < 0)
        exit(1);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    mmmmain(argc, argv);
    return (0);
}
