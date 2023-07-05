/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:14:09 by geudes            #+#    #+#             */
/*   Updated: 2023/06/15 03:42:06 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_lexer *lexer, t_lexer *end_lexer)
{
	t_node	*node;

	if (lexer == end_lexer)
		return (0);
	node = malloc(sizeof(t_node));
	if (!node)
		exit(1);
	node->opp = 0;
	node->lcmd = 0;
	if (look_for_first_opp(lexer, end_lexer))
		node->opp = create_opp(lexer, end_lexer);
	else
		node->lcmd = create_lcmd(lexer, end_lexer);
	return (node);
}
