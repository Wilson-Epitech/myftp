/*
** MYFTP PROJECT, 2024
** myftp
** File description:
** main
*/

int main(int ac, char **av)
{
    const char *usage = "\nUSAGE: ./myftp port path\n"
        "port is the port number on which the server socket listens\n"
        "path is the path to the home directory for the Anonymous user\n";

    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("%s", usage);
        return 0;
    }
    srv_function();
    return 0;
}