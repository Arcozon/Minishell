/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:33:08 by geudes            #+#    #+#             */
/*   Updated: 2023/02/07 05:22:55 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Returns 0 on succes 1 on error
// Av is a Null terminated char** with av[0] being the name of the function,
// and av[1]...av[n] the arguments
int	bi_env(char **av, t_env *env)
{
	(void)av;
	while (env)
	{
		printf("%s=%s\n", env->var_name, env->content);
		env = env->next;
	}
	return (1);
}
