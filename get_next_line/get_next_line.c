#include "get_next_line.h"

char *get_next_line(int fd)
{
    int     byte;
    char    c;
    char    *str_buffer;
    int     i;

    if (BUFFER_SIZE < 1 || fd < 0)
        return (NULL);
    i = 0;
    str_buffer = (char *)malloc(10000000);
    if (!str_buffer)
        return (NULL);
    byte = read(fd, &c, 1); // each every one character from txt file
    while (byte > 0)
    {
        str_buffer[i] = c;
        i++;
        if(c == '\n' || c == EOF)
            break ;
        byte = read(fd, &c, 1); // each every one character from txt file
    }
    // no more char OR error happens
    if (i == 0 || byte < 0)
    {
        free(str_buffer);
        return (NULL);
    }
    str_buffer[i] = '\0';
    return (str_buffer);
}

int main(void)
{
    int     fd;
    char    *str;
    char    *path;
    int     i;

    path = "test.txt";
    fd = open(path, O_RDONLY);
    i = 0;
    while(i < 10) // number of loop (test)
    {
        str = get_next_line(fd);
        printf("i: %i\n", i);
        printf("fd: %i, %s\n", fd, str);
        i++;
    }
    return (0);
}
