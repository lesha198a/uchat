#include "../../inc/client.h"

GtkWidget *label1;
GtkWidget *entryLogin;
GtkWidget *entryPass;
GtkWidget *window = NULL;

GtkWidget *create_window(void) {
    GtkBuilder *builder;
    GError *error = NULL;

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "resources/startupWindow.glade", &error)) {
        g_critical("Cannot load file: %s", error->message);
        g_error_free(error);
    }
    gtk_builder_connect_signals(builder, NULL);
    label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));

    window = GTK_WIDGET(gtk_builder_get_object(builder, "loginWindow"));

    entryLogin = GTK_WIDGET(gtk_builder_get_object(builder, "login"));

    entryPass = GTK_WIDGET(gtk_builder_get_object(builder, "password"));
    g_signal_connect(G_OBJECT(window),
                     "destroy", gtk_main_quit, NULL);
    if (!window) {
        g_critical("Error: on getting window widget");
    }
    g_object_unref(builder);

    return window;
}

bool mx_isspace(int c) {
    return (9 <= c && c <= 13) || (c == 32);
}

void skipSpaces(char *str) {
    int toskip = 0;
    while (mx_isspace(str[toskip]) && str[toskip] != '\0')
        toskip++;
    int i = 0;
    if (toskip == 0)
        return;
    for (; str[toskip] != '\0'; i++, toskip++)
        str[i] = str[toskip];
    str[i] = str[toskip];

}

G_MODULE_EXPORT void signin(GtkButton *button) {
    int stt = checkSignSTT();
    if (stt == 2 || stt == 0) {
        char login[32], password[32];
        snprintf(login, 31, "%8s", gtk_entry_get_text(GTK_ENTRY(entryLogin)));
        snprintf(password, 31, "%8s", gtk_entry_get_text(GTK_ENTRY(entryPass)));
        skipSpaces(login);
        skipSpaces(password);
        sendSignIn(login, password);
        usleep(1000);
        stt = checkSignSTT();
        if (stt == 2)
            gtk_label_set_text(GTK_LABEL(label1), "credentials error");
        else if (stt == 0)
            gtk_label_set_text(GTK_LABEL(label1), "waiting server respond... press \"sign in\" again");
    }
    if (stt == 1) {
        gtk_label_set_text(GTK_LABEL(label1), "signed in");
        usleep(500);
        gtk_window_close(GTK_WINDOW(window));
    }
}

G_MODULE_EXPORT void signup(GtkButton *button) {
    int stt = checkSignSTT();
    if (stt == 2 || stt == 0) {
        char login[32], password[32];
        snprintf(login, 31, "%8s", gtk_entry_get_text(GTK_ENTRY(entryLogin)));
        snprintf(password, 31, "%8s", gtk_entry_get_text(GTK_ENTRY(entryPass)));
        skipSpaces(login);
        skipSpaces(password);
        sendSignUp(login, password);
        usleep(1000);
        stt = checkSignSTT();
        if (stt == 2)
            gtk_label_set_text(GTK_LABEL(label1), "credentials error");
        else if (stt == 0)
            gtk_label_set_text(GTK_LABEL(label1), "waiting server respond... press \"sign up\" again");
    }
    if (stt == 1){
        gtk_label_set_text(GTK_LABEL(label1), "signed up");
        usleep(500);
        gtk_window_close(GTK_WINDOW(window));
    }
}
