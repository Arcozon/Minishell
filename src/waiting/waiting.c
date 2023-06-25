/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 02:34:49 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 05:40:09 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

struct mytimespec{
    unsigned long int sec;
    long int nano;
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
    (void)sig;
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
        myusleep(&one_sec);
}