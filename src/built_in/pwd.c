/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:43 by geudes            #+#    #+#             */
/*   Updated: 2023/07/18 14:22:42 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
{
	return (getcwd(0, 0));
}

// Returns 0 on succes 1 on error
int	bi_pwd(t_lcmd *lcmd, t_minishell *ms)
{
	char	*pwd;

	(void)ms;
	pwd = get_pwd();
	if (!pwd)
		return (write(lcmd->error, "Minishell: pwd: getcwd error\n", 30), 1);
	if (write(lcmd->output, pwd, ft_strlen(pwd)) != (ssize_t)ft_strlen(pwd)
		|| write(lcmd->output, "\n", 1) != 1)
		return (free(pwd), write(lcmd->error,
				"Minishell: pwd: write error\n", 28), 1);
	free(pwd);
	return (0);
}
