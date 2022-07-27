#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *res;
    int numline = 1;

    fd = open("test.txt", O_RDONLY);
    while (1)
    {
        res = get_next_line(fd);
        if (!res)
            break ;
        printf("%d | %s", numline++, res);
        free(res);
    }
    close(fd);
}