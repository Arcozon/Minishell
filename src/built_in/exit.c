/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:02:13 by geudes            #+#    #+#             */
/*   Updated: 2023/07/15 18:52:11 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_exit(t_minishell *ms, int exit_value)
{
	(void)exit_value;
	ft_exit_safely(ms);
}

void	ft_exit_safely(t_minishell *all)
{
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	free_ms(all);
	exit(g_cmd_exit);
}

//Return sex number cause noah is a silly little clown
int	bi_exit(t_lcmd *lcmd, t_minishell *ms)
{
	int	error;

	error = 2;
	if (lcmd)
		error = lcmd->error;
	write(error, "exit\n", 5);
	clean_exit(ms, g_cmd_exit);
	return (69);
}
