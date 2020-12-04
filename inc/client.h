#ifndef CLIENT_H
# define CLIENT_H

# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <limits.h>
# include <time.h>
# include <unistd.h>
# include <wchar.h>
# include <errno.h>
# include <netdb.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
#include <semaphore.h>

# include "lib.h"
# include "replies.h"
#include <gtk/gtk.h>
//#include <gtk/gtk>
/*
** Defines
*/
# define ERROR            -1
# define SUCCESS        0

# define DEFAULT_PORT    "1234"
# define LOCALHOST        "localhost"

# define CONNECT_LEN    7
# define QUIT_LEN        5

# define CRLF            2
# define LINE_START        1
# define CURSOR_START    3
# define BOX_INPUT_LEN    3
# define MAX_INPUT_LEN    510
# define MAX_NICK_LEN    16

# define IPV4_TYPE        4
# define IPV6_TYPE        6

# define BASIC_PORT_STR "Connecting to '%s' using default port '%s'"

extern pthread_t core;
extern pthread_mutex_t sign_lock;
extern sem_t sem_finish;
extern bool very_unsafe;

typedef struct s_client {
    int fd_max;
    fd_set read;
    fd_set write;
    fd_set master;
} t_client;

typedef struct s_circular {
    int head;
    int tail;
    int len;
    char buf[MAX_INPUT_LEN + CRLF];
} t_circular;

typedef struct s_user {
    char *nick;
    int socket;
    bool running;
    bool connected;
    char input[MAX_INPUT_LEN + CRLF];
    t_circular read;
    t_client client;
    bool loggedin;
} t_user;


/*
** Core
*/
void * running(void *user_conv);

void setInput (char *text);

void interpreter(t_user *user);

bool circular_get(t_user *user);

void circular_send(t_user *user);

void circular_push(t_circular *circ, char *data, int size);

bool search_for_crlf(char *buf, int head, int size);

void extract_and_update(t_circular *circ, char *final);

/* command */
void wrapper_connect(t_user *user, char **cmd);

bool irc_connect(t_user *user, char *ip, char *port);


G_MODULE_EXPORT void signin(GtkButton *button);

G_MODULE_EXPORT void signup (GtkButton *button);

void SignUpHandler (bool status);

void SignInHandler (bool status);

GtkWidget *create_window();

extern GtkWidget *chatWindow;

void init_chat_window(char *login);

/*cmd_linker*/

void sendSimpleMSG (char *text);

void sendSignIn (char *login, char *password);

void sendSignUp (char *login, char *password);

void respondHandler(char *decryptedText, t_user *user);

void sendJoinAndLeavePrev (char *toChat);

void sendLeave (char *Chat);

int checkSignSTT ();

bool isInputReady ();

void setInputReady(bool value);

int msgReceive (char **author, char **text);

void setNick(char *nick);

#endif
