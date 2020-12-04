#include "../../inc/client.h"

static void init_data(t_user *user) {
    ft_memset(user, 0x0, sizeof(t_user));
    ft_memset(&user->read, 0x0, sizeof(t_circular));
    user->running = true;
    user->connected = false;
    user->loggedin = false;
}

int main(int ac, char **av) {
    bool ret;
    t_user user;
    //t_interface	inter;

    ret = true;
    init_data(&user);
    if (ac == 3)
        ret = irc_connect(&user, av[1], av[2]);
    else {
        fprintf(stderr, "Usage: %s [ip] [port]'", av[0]);
        return 0;
    }
    if (ret == false) {
        fprintf(stderr, "Can't connect to %s:%s.", av[1], av[2]);
        return 0;
    }
    pthread_create(&core, NULL, &running, (void *) &user);
    GtkWidget *window;
    gtk_init(&ac, &av);
    window = create_window();
    gtk_widget_show(window);
    gtk_main();
    if (user.loggedin) {
        init_chat_window(user.nick);
        gtk_main();
    }
    very_unsafe = true;
    //sem_post(&sem_finish);
    pthread_join(core, NULL);
    //endwin();
    return 0;
}
