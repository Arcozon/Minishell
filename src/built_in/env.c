/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:33:08 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 09:18:34 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 0 on succes 1 on error
// Av is a Null terminated char** with av[0] being the name of the function,
// and av[1]...av[n] the arguments
int	bi_env(t_lcmd *lcmd, t_minishell *ms)
{
	t_env	*env;

	env = ms->env;
	while (env)
	{
		write(lcmd->output, env->var_name, ft_strlen(env->var_name));
		write(lcmd->output, "=", 1);
		write(lcmd->output, env->content, ft_strlen(env->content));
		write(lcmd->output, "\n", 1);
		env = env->next;
	}
	return (0);
}
