/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 22:56:53 by geudes            #+#    #+#             */
/*   Updated: 2023/06/09 09:01:31 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_opp *create_opp(t_lexer *lexer, t_lexer *end_lexer)
{
    t_opp   *opp;
    t_lexer *mid;

    opp = malloc(sizeof(t_opp)); 
    if (!opp)
        exit(1);
    mid = look_for_mid_opp(lexer, end_lexer);
    opp->logical_opp = mid->type;
    opp->l_node = create_node(lexer, mid);
    opp->r_node = create_node(mid->next, end_lexer);
    return (opp);
}

//might do exactly the same as lookforlastopp
//EXEPT IF ALL THE CMD IS IN PARENTHESYS
t_lexer *look_for_mid_opp(t_lexer *lexer, t_lexer *end_lexer)
{
    t_lexer *mid;
    
    if (!lexer)
        return (0);
    mid = look_for_last_opp(lexer, end_lexer);
    if (!mid)
        mid = look_for_last_opp(lexer->next, end_lexer);
    return (mid);     
}
