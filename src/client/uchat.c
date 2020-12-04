#include "../../inc/client.h"
GtkWidget *chatWindow;
GtkWidget *sendEntry, *sendButton;
GtkWidget *statusLabel;
GtkWidget *chanLabel;
GtkWidget *messagesTreeView;
GtkWidget *chanEntry, *joinChan;
GtkAdjustment *vAdjust;
GtkScrolledWindow *scrolledWindow;
GtkListStore *messagesListStore;
pthread_t watcher;

#define REQUEST_HISTORY 10



void add_list_entry(const char *a, const char *m, int sleep)
{
    GtkTreeIter iter;
    gtk_list_store_append(GTK_LIST_STORE(messagesListStore), &iter);
    gtk_list_store_set(GTK_LIST_STORE(messagesListStore), &iter, 0, 0, 1, a, 2, m, -1);//second zero was time
    if(sleep)
        usleep(100);
    gtk_adjustment_set_value(vAdjust, gtk_adjustment_get_upper(vAdjust) - gtk_adjustment_get_page_size(vAdjust));
}

void do_join() {
    if(!gtk_widget_get_sensitive(joinChan))
        return;
    gtk_label_set_text(GTK_LABEL(statusLabel), "");
    const gchar *message;
    message = gtk_entry_get_text(GTK_ENTRY(chanEntry));
    if(!message || !*message)
        return;
    char *m = malloc(strlen(message) + 1);
    strcpy(m, message);
    gtk_label_set_text(GTK_LABEL(chanLabel), m);
    //gtk_entry_set_text(GTK_ENTRY(sendEntry), "");
    sendJoinAndLeavePrev(m);
    gtk_list_store_clear(GTK_LIST_STORE(messagesListStore));
    usleep(1000);
    sendSimpleMSG("/gethistory\r\n");
    //free(m);
}

void do_send()
{
    if(!gtk_widget_get_sensitive(sendButton))
        return;
    gtk_label_set_text(GTK_LABEL(statusLabel), "");
    const gchar *message;
    message = gtk_entry_get_text(GTK_ENTRY(sendEntry));
    if(!message || !*message)
        return;
    if(strlen(message)==0)
        return;
    char *m = malloc(strlen(message) + 1);
    strcpy(m, message);
    gtk_entry_set_text(GTK_ENTRY(sendEntry), "");
    sendSimpleMSG(m);
    free(m);
}

void *watcher_thread(void *param)
{
    (void) param;
    char *author, *body;
    //message_request_history(REQUEST_HISTORY);

    while(1)
    {
        int k = msgReceive(&author, &body);
        if(k < 0)
        {
            gtk_label_set_text(GTK_LABEL(statusLabel), "Disconnected, please restart the client");
            gtk_widget_set_sensitive(sendButton, 0);
            break;
        }
        if(k == 0)
            continue;
        if(!author)
        {
            gtk_label_set_text(GTK_LABEL(statusLabel), body);
            continue;
        }
        add_list_entry(author, body, k != 'h');
        free(author);
        free(body);
        usleep(50);
    }
    return param;
}

void init_chat_window(char *login)
{
    GtkBuilder *builder = gtk_builder_new_from_file("resources/uchat.glade");
    chatWindow = GTK_WIDGET(gtk_builder_get_object(builder,"chatWindow"));
    char buf[100] = "UCHAT | you are ";
    strcat(buf, login);
    gtk_window_set_title(GTK_WINDOW(chatWindow), buf);
    g_signal_connect(chatWindow,"destroy", G_CALLBACK(gtk_main_quit),NULL);
    sendEntry = GTK_WIDGET(gtk_builder_get_object(builder,"sendEntry"));
    sendButton = GTK_WIDGET(gtk_builder_get_object(builder,"sendButton"));
    g_signal_connect(G_OBJECT(sendEntry),"activate", G_CALLBACK(do_send),NULL);
    g_signal_connect(G_OBJECT(sendButton),"clicked", G_CALLBACK(do_send),NULL);
    statusLabel = GTK_WIDGET(gtk_builder_get_object(builder,"statusLabel"));
    chanEntry = GTK_WIDGET(gtk_builder_get_object(builder,"EntryChannel"));
    joinChan = GTK_WIDGET(gtk_builder_get_object(builder,"ChannelButton"));
    chanLabel = GTK_WIDGET(gtk_builder_get_object(builder,"chanLabel"));
    g_signal_connect(G_OBJECT(chanEntry),"activate", G_CALLBACK(do_join),NULL);
    g_signal_connect(G_OBJECT(joinChan),"clicked", G_CALLBACK(do_join),NULL);
    messagesTreeView = GTK_WIDGET(gtk_builder_get_object(builder,"messagesTreeView"));
    messagesListStore = GTK_LIST_STORE(gtk_builder_get_object(builder,"messagesListStore"));
    scrolledWindow = GTK_SCROLLED_WINDOW(gtk_builder_get_object(builder,"scrolledWindow"));
    vAdjust = gtk_scrolled_window_get_vadjustment(scrolledWindow);
    pthread_create(&watcher, 0, watcher_thread, 0);
    gtk_widget_show(chatWindow);
}
