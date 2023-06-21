/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 02:34:49 by geudes            #+#    #+#             */
/*   Updated: 2023/06/21 03:43:51 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

struct mytimespec{
    long int sec;
    long int nano;
    int:32;
};

void myusleep(struct mytimespec *var)
{    
    asm volatile("mov $35, %rax;"
    "mov -8(%rsp), %rdi;"
    "xor %rsi, %rsi;"
    "syscall");
    (void) var;
}

void    handler(int sig)
{
    static int  toggle = 0;
    static int  i = 0;
    static char *loading = "|/-\\";

    if (sig == SIGUSR1)
    {
        toggle ^= 1;
        if (toggle)
            write(1, "\033[?25l\\", 7);
        else
            write(1, "\x8\033[?25h", 7);
            
    }
    else if (toggle)
    {
        write(1, "\x8",1);
        write(1, loading + i, 1);
        ++i;
        i %= 4;
    }
}

__attribute__((constructor))
void    set_sig(void)
{
    struct sigaction    sa;

    sa.sa_handler = handler;
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, 0) == -1)
        exit(1);
}

int main(void)
{
    struct mytimespec one_sec;

    one_sec.sec = 1;
    one_sec.nano = 0;
    while (1)
    {
        myusleep(&one_sec);
        handler(-1);
    }
}