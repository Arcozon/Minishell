/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:27:46 by geudes            #+#    #+#             */
/*   Updated: 2023/07/18 16:28:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define HOME "HOME"

static char	checkerrorfilename(char *argv1)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (argv1[i])
	{
		if (argv1[i] == '/')
			len = 0;
		else
			++len;
		if (len >= 256)
			return (1);
		++i;
	}
	return (0);
}

static char	*dup_home(t_env *env)
{
	while (env && ft_strcmp(env->var_name, HOME))
		env = env->next;
	if (env)
		return (ft_strdup(env->content));
	return (0);
}

static char	*join_with_home(t_lcmd *lcmd, t_env *env)
{
	char	*home;
	char	*res;

	home = dup_home(env);
	if (!home)
		return (write(lcmd->error, "Minishell: cd: No HOME\n", 23), NULL);
	res = ft_strjoin(home, lcmd->cmd[1] + 1);
	free(home);
	if (!res)
		return (write(lcmd->error, "Minishell: cd: Malloc error\n", 28), NULL);
	return (res);
}

static char	*get_path(t_lcmd *lcmd, t_env *env)
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
	if (checkerrorfilename(lcmd->cmd[1]))
		return (write(lcmd->error, "Minishell: cd: File name too long\n", 34),
			(char *)0);
	if (lcmd->cmd[1][0] != '/' && lcmd->cmd[1][0] != '~')
	{
		pwd = get_pwd();
		if (!pwd)
			return (write(lcmd->error, "Minishell: cd: Malloc error\n", 28)
				, (char *)0);
		path = ft_strjoin_with_slash(pwd, lcmd->cmd[1]);
		return (free(pwd), path);
	}
	if (lcmd->cmd[1][0] == '~')
		return (join_with_home(lcmd, env));
	return (ft_strdup(lcmd->cmd[1]));
}

// Returns 0 on succes 1 on error
int	bi_cd(t_lcmd *lcmd, t_minishell *ms)
{
	char	*path;

	if (!lcmd->cmd[1])
	{
		path = dup_home(ms->env);
		if (!path)
			return (write(lcmd->error, "Minishell: cd: No HOME\n", 23), 1);
	}
	else
		path = get_path(lcmd, ms->env);
	if (!path)
		return (1);
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
