//
// Created by Oleksii Kalnytskyi on 11/22/20.
//
#include "../inc/server.h"

int main (int argv, char **argc) {
    /* initialize glib */
    g_type_init ();

    GError * error = NULL;

    /* create a new connection */
    GSocketConnection * connection = NULL;
    GSocketClient * client = g_socket_client_new();

    /* connect to the host */
    connection = g_socket_client_connect_to_host (client,
                                                  (gchar*)"localhost",
                                                  1500, /* your port goes here */
                                                  NULL,
                                                  &error);

    /* don't forget to check for errors */
    if (error != NULL)
    {
        g_error (error->message);
    }
    else
    {
        g_print ("Connection successful!\n");
    }

    /* use the connection */
    GInputStream * istream = g_io_stream_get_input_stream (G_IO_STREAM (connection));
    GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));
    g_output_stream_write  (ostream,
                            "Hello server!", /* your message goes here */
                            13, /* length of your message */
                            NULL,
                            &error);
    /* don't forget to check for errors */
    if (error != NULL)
    {
        g_error (error->message);
    }
    return 0;
}
