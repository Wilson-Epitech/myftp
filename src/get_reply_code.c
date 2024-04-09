/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** reply_code
*/

#include "server.h"
#include <string.h>

char *get_reply_code(char *str)
{
    char **reply = NULL;
    char **array = NULL;

    reply = init_array_reply(reply);
    for (int i = 0; reply[i] != NULL; i++) {
        array = my_word_array_delim(reply[i], " ");
        if (strcmp(array[0], str) == 0) {
            return strdup(reply[i]);
        }
    }
    return NULL;
}

void send_reply(int sd, char *reply_code)
{
    char *message = get_reply_code(reply_code);

    write(sd, message, strlen(message));
}
