/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 10:02:13 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 09:21:21 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Return nothing
void	bi_exit(t_lcmd *lcmd, t_minishell *ms)
{
	int	error;

	error = 2;
	if (lcmd)
		error = lcmd->error;
	write(error, "exit\n", 5);
	rl_clear_history();
	free_ms(ms);
	exit (g_cmd_exit);
}
