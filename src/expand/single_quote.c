/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:49:35 by geudes            #+#    #+#             */
/*   Updated: 2023/02/11 18:37:52 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_sq(t_lexer *root, t_env *env)
{
	int		get_next_sq;
	char	*buff_content;

	(void)env;
	if (root->content[0] == '\'')
	{
		get_next_sq = 1;
		while (root->content[get_next_sq]
			&& root->content[get_next_sq] != '\'')
			get_next_sq++;
		if (root->content[get_next_sq] == '\'')
		{
			buff_content = ft_strdup(root->content);
			free(root->content);
			root->content = ft_substr(buff_content, 1, get_next_sq - 1);
			root->type = TEXT;
			free(buff_content);
		}
	}
}
