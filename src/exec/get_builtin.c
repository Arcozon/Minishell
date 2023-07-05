/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 09:59:51 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 12:20:30 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static const char	*g_builtin[] = {"cd", "export", "unset", "pwd", "echo",
	"env", "exit", "owo", "clear", 0};

static int (*const	g_bi_func[])() = {bi_cd, bi_export, bi_unset, bi_pwd,
	bi_echo, bi_env, bi_exit, bi_owo, bi_clear};

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2
		&& (unsigned const char)*str1 == (unsigned const char)*str2)
	{
		str1++;
		str2++;
	}
	return ((unsigned const char)*str1 - (unsigned const char)*str2);
}

int	ft_is_builtin(t_lcmd *cmd, t_minishell *all)
{
	int	i;

	i = 0;
	while (g_builtin[i])
	{
		if (cmd->cmd && cmd->cmd[0] && !ft_strcmp(*(cmd->cmd), g_builtin[i]))
		{
			g_cmd_exit = i[g_bi_func](cmd, all);
			return (1);
		}
		i++;
	}
	return (0);
}
