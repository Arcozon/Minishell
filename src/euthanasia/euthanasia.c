/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   euthanasia.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 02:34:49 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 07:57:46 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

struct	s_mytimespec
{
	unsigned long int	sec;
	long int			nano;
};

void	myusleep(struct mytimespec *var)
{
	asm volatile ("mov $35, %rax;"
		"mov -8(%rsp), %rdi;"
		"xor %rsi, %rsi;"
		"syscall");
	(void)var;
}

void	handle(int sig, siginfo_t *info, void *context)
{
	(void)context;
	(void)sig;
	kill(info->si_pid, SIGKILL);
	exit(0);
}

__attribute__((constructor))
void	sig_eutanasia(void)
{
	struct sigaction	sigusr;

	sigusr.sa_flags = SA_SIGINFO;
	sigusr.sa_sigaction = handle;
	sigemptyset(&sigusr.sa_mask);
	if (sigaction(SIGUSR1, &sigusr, 0))
		exit(0);
}

int	euthanasia(void)
{
	struct s_mytimespec	one_sec;
	int					pid;

	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid)
		return (pid);
	sig_eutanasia();
	one_sec.sec = 1;
	one_sec.nano = 0;
	while (1)
		myusleep(&one_sec);
}
