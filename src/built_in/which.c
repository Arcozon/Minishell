/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:47:38 by geudes            #+#    #+#             */
/*   Updated: 2023/06/30 19:42:00 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**which_get_path(t_env *env)
{
{
	while (env)
	{
		if (!ft_strcmp(env->var_name, "PATH"))
			return (ft_split(env->content, ':'));
		env = env->next;
	}
	return (0);
}
}

static char	*which_get_working_path(char **path, char *cmd)
{
	char	*tmp;
    char    *pwd;
	int		i;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin_with_slash(path[i], cmd);
		if (access(tmp, F_OK | X_OK) != -1)
			return (tmp);
		free(tmp);
		i++;
	}
    pwd = get_pwd();
    tmp = ft_strjoin_with_slash(pwd, cmd);
    free(pwd);
	if (access(tmp, F_OK | X_OK) != -1)
		return (tmp);
	return (free(tmp), (char *)0);
}

int     bi_which(t_lcmd *lcmd, t_env *env)
{
    int     myint;
    int     return_v;
    char    **path;
    char    *cmd_path;

    myint = 1;
    return_v = lcmd->cmd[1] == 0;
    path = which_get_path(env);
    while (lcmd->cmd[myint])
    {
        cmd_path = which_get_working_path(path, lcmd->cmd[myint]);
        ++myint;
        if (!cmd_path)
        {
            return_v = 1;
            continue ;
        }
        write(lcmd->output, cmd_path, ft_strlen(cmd_path));
        write(lcmd->output, "\n", 1);
        free(cmd_path);
    }
    return (return_v);
}