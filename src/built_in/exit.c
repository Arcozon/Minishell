/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:02:13 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 13:26:12 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	clean_exit(t_minishell *ms, int exit_value)
{
	rl_clear_history();
	free_ms(ms);
	exit (exit_value);
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
