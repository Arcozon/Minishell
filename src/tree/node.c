/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:14:09 by geudes            #+#    #+#             */
/*   Updated: 2023/06/08 07:07:47 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node   *create_node(t_lexer *lexer)
{
    t_node   *node;

    node = malloc(sizeof(t_node));
    if (!node)
        exit(1);
    node->opp = 0;
    node->lcmd = 0;
    if (look_for_opp(lexer))
        node->opp = create_opp(lexer);
    else
        node->lcmd = create_lcmd(lexer); 
    return (node);
}

