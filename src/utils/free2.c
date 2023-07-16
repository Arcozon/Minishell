/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:11:53 by geudes            #+#    #+#             */
/*   Updated: 2023/07/16 19:40:44 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	am_i_in_trash(t_lexer *me, t_lexer *trash)
{
	while (trash)
	{
		if (me == trash)
			return (1);
		trash = trash->next;
	}
	return (0);
}

void	free_lexer(t_lexer *root, t_lexer *trash)
{
	t_lexer	*next;

	while (root)
	{
		next = root->next;
		if (!am_i_in_trash(root, trash))
			(free(root->content), free(root));
		root = next;
	}
}

void	free_env(t_env *env)
{
	t_env	*next;

	while (env)
	{
		next = env->next;
		free(env->content);
		free(env->var_name);
		free(env);
		env = next;
	}
}

void	free_trash(t_minishell *ms)
{
	t_lexer	*root;
	t_lexer	*next;

	root = ms->trash_wc;
	while (root)
	{
		next = root->next;
		free(root->content);
		free(root);
		root = next;
	}
	root = 0;
	ms->trash_wc = 0;
}
