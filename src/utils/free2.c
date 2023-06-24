/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:11:53 by geudes            #+#    #+#             */
/*   Updated: 2023/06/24 12:48:21 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	free_lexer(t_lexer *root)
{
	t_lexer	*next;

	while (root)
	{
		next = root->next;
		free(root->content);
		free(root);
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
