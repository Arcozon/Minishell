/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:16:00 by geudes            #+#    #+#             */
/*   Updated: 2023/06/08 08:58:46 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lcmd   *create_lcmd(t_lexer *lexer)
{
    t_lcmd   *lcmd;

    if (!lexer)
        return (0);
    if (lexer->type == PIPE)
        lexer = lexer->next;
    lcmd = malloc(sizeof(t_lcmd));
    if (!lcmd)
        exit(1);
    lcmd->input = 0;
    lcmd->output = 1;
    lcmd->error = 2;
    lcmd->ioe_put = create_ioeput(lexer);
    lcmd->cmd = create_cmd(lexer);
    lcmd->next = create_lcmd(look_for_pipe(lexer));
    return (lcmd);
}

static int count_cmdargs(t_lexer *lexer, t_lexer *end_cmd)
{
    int     count;

    count = 0;
    while (lexer != end_cmd)
    {
        if (lexer->type == CMD || lexer->type == ARGS)
            ++count;
        lexer = lexer->next;
    }
    return (count);
}

char    **create_cmd(t_lexer *lexer)
{
    t_lexer *end_cmd;
    int     count;
    char    **cmd;

    end_cmd = look_for_end_cmd(lexer);
    count = count_cmdargs(lexer, end_cmd);
    cmd = malloc(sizeof(char *) * (count + 1));
    if (!cmd)
        exit(1);
    cmd[count] = 0;
    count = 0;
    while (lexer != end_cmd)
    {
        if (lexer->type == CMD || lexer->type == ARGS)
        {
            cmd[count] = ft_strdup(lexer->content);
            ++count;
        }
        lexer = lexer->next;
    }
    return (cmd);
}

static int is_there_ioe(t_lexer *lexer)
{
    static char is_ioe[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0};
    t_lexer     *end_cmd;
    
    end_cmd = look_for_end_cmd(lexer);
    while (lexer != end_cmd)
    {
        if (is_ioe[lexer->type])
            return (1);
        lexer = lexer->next;
    }
    return (0);
}

t_ioe_put   *create_ioeput(t_lexer *lexer)
{
    static char is_ioe[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0,
        0, 0, 0, 0, 0};
    t_lexer     *end_cmd;
    t_ioe_put   *ioe_put;

    end_cmd = look_for_end_cmd(lexer);
    if (!is_there_ioe(lexer))
        return (0);
    ioe_put = malloc(sizeof(ioe_put));
    if (!ioe_put)
        exit(1);
    while (lexer != end_cmd)
    {
        if (is_ioe[lexer->type])
        {
            ioe_put->type = lexer->type;
            ioe_put->name = ft_strdup(lexer->next->content);
            ioe_put->next = create_ioeput(lexer->next);
            return (ioe_put);
        }
        lexer = lexer->next;
    }
    return (0);
}