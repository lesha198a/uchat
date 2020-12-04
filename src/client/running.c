
#include "../../inc/client.h"

t_user *user1;

pthread_t core;
pthread_mutex_t sign_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sem_finish;
bool very_unsafe = false;

void setInput(char *text) {
    char *buf = strndup(text, 511);
    strcpy(user1->input, buf);
    //free(buf);
    setInputReady(true);
}

void setUser(t_user *user) {
    user1 = user;
}

void setNick(char *nick) {
    user1->nick = strdup(nick);
}

static void init_fd(t_user *user) {
    FD_ZERO(&user->client.read);
    FD_ZERO(&user->client.write);
    FD_ZERO(&user->client.master);
    FD_SET(STDIN_FILENO, &user->client.master);
}

static void reset_data(char *buf) {
    ft_memset(buf, 0x0, MAX_INPUT_LEN + CRLF);
    setInputReady(false);
    //todo clearing entry
}

static void read_from_user(t_user *user) {
    if (strlen(user->input) > 0 && strlen(user->input) < MAX_INPUT_LEN) {
        interpreter(user);
        reset_data(user->input);
    }

}

static void read_from_server(t_user *user) {
    char buf[MAX_INPUT_LEN + CRLF];

    memset(buf, 0x0, MAX_INPUT_LEN + CRLF);
    if (circular_get(user) != true) {
        FD_CLR(user->socket, &user->client.master);
        close(user->socket);
        user->connected = false;
        //todo check it
        //refresh_top_interface(inter, "Disconnected from server :_:\n");
        return;
    }
    while (search_for_crlf(user->read.buf, user->read.head, user->read.len)) {
        extract_and_update(&user->read, buf);
        respondHandler(buf, user);
        //refresh_top_interface(inter, "%s", buf);
    }
}

void *running(void *user) {
    t_user *user_conv = (t_user *) user;
    init_fd(user_conv);
    setUser(user_conv);
    while (user_conv->running == true) {
        user_conv->client.read = user_conv->client.master;
        user_conv->client.write = user_conv->client.master;
        if (user_conv->connected == true && \
            !FD_ISSET(user_conv->socket, &user_conv->client.master))
            FD_SET(user_conv->socket, &user_conv->client.master);
        if (select(user_conv->socket + 1, &user_conv->client.read, \
                &user_conv->client.write, NULL, NULL) < 0)
            return NULL;
        if (isInputReady())
            read_from_user(user_conv);
        else if (user_conv->connected == true && \
            FD_ISSET(user_conv->socket, &user_conv->client.read))
            read_from_server(user_conv);
        if (very_unsafe) {
            return NULL;
        }
        //usleep(100);
    }
    return NULL;
}
