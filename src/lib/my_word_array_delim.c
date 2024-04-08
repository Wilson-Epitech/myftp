/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** my_word_array_delim
*/

#include <stdbool.h>
#include <stdlib.h>

static bool is_delim(char c, char *separators)
{
    for (int i = 0; separators[i] != '\0'; i++) {
        if (c == separators[i]) {
            return true;
        }
    }
    return false;
}

static int count_i_nb_words(char const *str, int i, char *separators)
{
    while (is_delim(str[i], separators)) {
        i++;
    }
    return i;
}

static int get_nb_words(char const *str, char *separators)
{
    int i = 0;
    int nb = 0;

    while (str[i] != '\0') {
        if (is_delim(str[i], separators)) {
            nb++;
            i = count_i_nb_words(str, i, separators);
        } else {
            i++;
        }
    }
    return nb + 1;
}

static int get_word_length(char const *str, int i, char *separators)
{
    int count = 0;

    while (!is_delim(str[i], separators) && str[i] != '\0') {
        count++;
        i++;
    }
    return count;
}

static char *parse_word(char const *str, int *i, char *separators)
{
    int y = 0;
    int word_length = get_word_length(str, *i, separators);
    char *word = malloc(sizeof(char) * (word_length + 1));

    if (word == NULL)
        return NULL;
    while (!is_delim(str[*i], separators) && str[*i] != '\0') {
        word[y] = str[*i];
        (*i)++;
        y++;
    }
    word[y] = '\0';
    return word;
}

char **my_word_array_delim(char const *str, char *separators)
{
    int i = 0;
    int x = 0;
    int nb_words = get_nb_words(str, separators);
    char **result = malloc(sizeof(char *) * (nb_words + 1));

    if (result == NULL)
        return NULL;
    while (str[i] != '\0') {
        if (is_delim(str[i], separators)) {
            i++;
        } else {
            result[x] = parse_word(str, &i, separators);
            x++;
        }
    }
    result[x] = NULL;
    return result;
}
