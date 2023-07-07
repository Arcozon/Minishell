#include <fcntl.h>
#include <unistd.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    if (str)
        while (str[i])
            i++;
    return (i);
}

int ft_putchar(char c)
{
    return (write(STDOUT_FILENO, &c, 1));
}

void ft_putnbr(int nbr)
{
    if (nbr < 0)
    {
        nbr = -nbr;
        ft_putchar('-');
    }
    if (nbr < 9)
    {
        ft_putchar(nbr + '0');
    }
    else {
        ft_putnbr(nbr / 10);
        ft_putchar(nbr % 10);
    }
}

int ft_check_eof(int *br, char *str, int len)
{
    char buf[1];
    int i;

    i = -1;
    while (*br != 0 && ++i < len)
    {
        *br = read(STDIN_FILENO, buf, 1);
        if (*br == -1)
            return (-1);
        if (*br == 0 || buf[0] != i[str])
            break ;
    }
    if (i == len)
    {
        *br = read(STDIN_FILENO, buf, 1);
        if (*br == -1)
            return (-1);
        if (*br == 0 || buf[0] == '\n')
            return (0);
    }
    write(STDOUT_FILENO, str, i);
    if (i < len || (i == len && buf[0] != '\n'))
        write(STDOUT_FILENO, buf, 1);
    return (1);
}

int ft_read_stdin(char *str, int len)
{
    char buf[1];
    int br;
    int status;

    br = 1;
    status = 0;
    while (br != 0)
    {
        br = read(STDIN_FILENO, buf, 1);
        if (br == -1)
            return (-1);
        if (br == 0)
            break ;
        write(STDOUT_FILENO, buf, 1);
        if (buf[0] == 10)
        {
            status = ft_check_eof(&br, str, len);
            if (status == -1)
                return (-1);
            else if (status == 0)
                break ;
        }
    }
    return (0);
}


int main(void)
{
    char str[] = {"EOF"};
    int len = ft_strlen(str);
    return (ft_read_stdin(str, len));
}
