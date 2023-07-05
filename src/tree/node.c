/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:14:09 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 13:27:51 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_lexer *lexer, t_lexer *end_lexer, t_minishell *ms)
{
	t_node	*node;

	if (lexer == end_lexer)
		return (0);
	node = malloc(sizeof(t_node));
	awaiting_death(!node, ms);
	node->opp = 0;
	node->lcmd = 0;
	if (look_for_first_opp(lexer, end_lexer))
		node->opp = create_opp(lexer, end_lexer, ms);
	else
		node->lcmd = create_lcmd(lexer, end_lexer, ms);
	return (node);
}
