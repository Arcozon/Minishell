/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:46 by geudes            #+#    #+#             */
/*   Updated: 2023/06/25 09:11:40 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define HOME "HOME"

static char	*dup_home(t_env *env)
{
	while (env && ft_strcmp(env->var_name, HOME))
		env = env->next;
	if (env)
		return (ft_strdup(env->content));
	return (0);
}

static char	*get_path(t_lcmd *lcmd)
{
	char	*path;
	char	*pwd;
	int		ac;

	ac = 0;
	while (lcmd->cmd[ac])
		ac++;
	if (ac > 2)
		return (write(lcmd->error, "Minishell: cd: Too many arguments\n",
				34), (char *)0);
	if (ft_strlen(lcmd->cmd[1]) > 255)
		return (write(lcmd->error, "Minishell: cd: File name too long\n", 34),
			(char *)0);
	if (lcmd->cmd[1][0] != '/' && lcmd->cmd[1][0] != '~')
	{
		pwd = get_pwd();
		if (!pwd)
			return (0);
		path = ft_strjoin_with_slash(pwd, lcmd->cmd[1]);
		free(pwd);
		return (path);
	}
	return (ft_strdup(lcmd->cmd[1]));
}

// Returns 0 on succes 1 on error
int	bi_cd(t_lcmd *lcmd, t_env *env)
{
	char	*path;

	if (!lcmd->cmd[1])
	{
		path = dup_home(env);
		if (!path)
			return (write(lcmd->error, "Minishell: cd: No HOME\n", 23), 1);
	}
	else
		path = get_path(lcmd);
	if (!path)
		return (write(lcmd->error, "Minishell: cd: Pwd error\n", 25), 1);
	if (chdir(path))
	{
		write (lcmd->error, "Minishell: cd :", 15);
		write (lcmd->error, lcmd->cmd[1], ft_strlen(lcmd->cmd[1]));
		write (lcmd->error, ": No such file or directory\n", 28);
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
