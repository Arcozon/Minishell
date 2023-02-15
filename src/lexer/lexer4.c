/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 00:09:13 by geudes            #+#    #+#             */
/*   Updated: 2023/02/15 04:11:45 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*lexer_new(int type, char *content)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (!new)
	{
		write(2, "Minishel: lexer: malloc error\n", 30);
		return (0);
	}
	new->content = content;
	new->type = type;
	new->next = 0;
	return (new);
}

void	lexer_add_back(t_lexer **root, t_lexer *new)
{
	if (!root)
		return ;
	while (*root)
		root = &((*root)->next);
	*root = new;
}
