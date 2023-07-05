/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 09:59:51 by geudes            #+#    #+#             */
/*   Updated: 2023/06/29 10:07:42 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#define BUILTINNBR 7
#define BUILTINSPLIT 3

static char	*g_builtin[] = {"cd", "export", "unset", "pwd", "echo", "env",
	"exit"};

static int	(*g_bi_func[])() = {bi_cd, bi_export, bi_unset, bi_pwd, bi_echo,
	bi_env};

int	ft_strcmp(char *str1, char *str2)
{
	while (*str1 && *str2 && (unsigned char)*str1 == (unsigned char)*str2)
	{
		str1++;
		str2++;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

void	ft_exec_builtin(t_lcmd *cmd, t_env *env, int nbr)
{
	if (nbr == 0)
		g_cmd_exit = (g_bi_func[nbr])(cmd, env);
	else if (nbr > 0 && nbr <= BUILTINSPLIT)
		g_cmd_exit = (g_bi_func[nbr])(cmd, &env);
	else if (nbr > BUILTINSPLIT && nbr < BUILTINNBR - 1)
		g_cmd_exit = (g_bi_func[nbr])(cmd, env);
	else if (nbr == BUILTINNBR - 1)
		bi_exit();
}

int	ft_is_builtin(t_lcmd *cmd, t_env *env)
{
	int	i;

	i = 0;
	while (i < BUILTINNBR)
	{
		if (cmd->cmd && cmd->cmd[0] && !ft_strcmp(*(cmd->cmd), g_builtin[i]))
		{
			ft_exec_builtin(cmd, env, i);
			return (1);
		}
		i++;
	}
	return (0);
}
