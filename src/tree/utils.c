/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:13:16 by geudes            #+#    #+#             */
/*   Updated: 2023/06/08 03:33:16 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer  *look_for_opp(t_lexer *lexer)
{
    while(lexer)
    {
        if (lexer->type == OR || lexer->type == AND)
            return (lexer);
        lexer = lexer->next;
    }
    return (0);
}

t_lexer  *look_for_pipe(t_lexer *lexer)
{
    t_lexer *last;

    last = look_for_opp(lexer);
    while(lexer != last)
    {
        if (lexer->type == PIPE)
            return (lexer);
        lexer = lexer->next;
    }
    return (0);
}

t_lexer  *look_for_end_cmd(t_lexer *lexer)
{
    t_lexer *end_cmd;

    end_cmd = look_for_pipe(lexer);
    if (!end_cmd)
        end_cmd = look_for_opp(lexer);
    return (end_cmd);
}