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

static inline int ft_putchar(char c)
{
    return (write(STDOUT_FILENO, &c, 1) > 0);
}

int ft_putstr(char *str)
{
    int i;

    i = 0;
    if (str)
    {
        while (*str)
        {
            i |= ft_putchar(*str);
            str++;
        }
    }
    return (i);
}

int ft_heredoc_perror(char *str)
{
    int i;

    i = ft_putstr("Minishell: warning: here-document at line 1 delimited by"
            " end-of-file (wanted '");
    i <<= 1;
    i += ft_putstr(str);
    i <<= 1;
    i +=ft_putstr("')\n");
    return (i);
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

int ft_check_eof(int fd, char buf[1], char *str, int len)
{
    int i;
    int br;

    i = -1;
    br = 1;
    while (br != 0 && ++i < len)
    {
        br = read(STDIN_FILENO, buf, 1);
        if (br == -1)
            return (-1);
        if (br == 0 || buf[0] != i[str])
            break ;
    }
    if (i == len)
    {
        br = read(STDIN_FILENO, buf, 1);
        if (br == -1)
            return (-1);
        if (buf[0] == '\n')
            return (0);
    }
    write(STDOUT_FILENO, str, i);
    if (i < len || (i == len && buf[0] != '\n'))
        write(STDOUT_FILENO, buf, 1);
    return (1 + (br == 0));
}

int ft_read_stdin(int fd, char *str, int len)
{
    char buf[1];
    int br;
    int status;

    br = 1;
    status = 1;
    buf[0] = 0;
    write(STDOUT_FILENO, "> ", 2);
    while (br != 0)
    {
        status = ft_check_eof(fd, buf, str, len);
        if (status == 0)
            break ;
        else if (status == -1)
            return (-1);
        else if (status == 2)
            return (ft_heredoc_perror(str), 0);
        while (buf[0] != '\n')
        {
            br = read(STDIN_FILENO, buf, 1);
            if (br == -1)
                return (-1);
            write(STDOUT_FILENO, buf, 1);
        }
        write(STDOUT_FILENO, "> ", 2);

    }
    return (0);
}


int main(void)
{
    char str[] = {"dio"};
    int len = ft_strlen(str);
    int fd = open("test.ty", O_CREAT | O_TRUNC | O_WRONLY, 0622);
    ft_read_stdin(fd, str, len);
    close(fd);
    return (0);
}
