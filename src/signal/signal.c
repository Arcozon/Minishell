/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:16:45 by geudes            #+#    #+#             */
/*   Updated: 2023/07/16 18:01:17 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

void	sig_routine(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_cmd_exit = 130;
	}
}

void	sig_exec(int sig)
{
	if (sig == SIGINT)
	{
		g_cmd_exit = 130;
		write(1, "\n", 1);
	}
	else if (sig == SIGQUIT)
	{
		g_cmd_exit = 131;
	}
}

void	set_sig_routine(void)
{
	struct sigaction	s_routine;

	s_routine.sa_flags = 0;
	s_routine.sa_handler = sig_routine;
	sigemptyset(&s_routine.sa_mask);
	if (sigaction(SIGINT, &s_routine, 0))
		exit(1);
	s_routine.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &s_routine, 0))
		exit(1);
}

void	set_sig_exec(void)
{
	struct sigaction	s_exec;

	s_exec.sa_flags = 0;
	s_exec.sa_handler = sig_exec;
	sigemptyset(&s_exec.sa_mask);
	if (sigaction(SIGINT, &s_exec, 0))
		exit(1);
	if (sigaction(SIGQUIT, &s_exec, 0))
		exit(1);
}

void	set_sig_heredoc(void)
{
	struct sigaction	s_routine;

	s_routine.sa_flags = 0;
	s_routine.sa_handler = sig_exec;
	sigemptyset(&s_routine.sa_mask);
	if (sigaction(SIGINT, &s_routine, 0))
		exit(1);
	s_routine.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &s_routine, 0))
		exit(1);
}
