/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 23:16:00 by geudes            #+#    #+#             */
/*   Updated: 2023/07/16 09:49:28 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lcmd	*create_lcmd(t_lexer *lexer, t_lexer *end_lexer, t_minishell *ms)
{
	t_lcmd	*lcmd;

	if (!lexer || lexer == end_lexer)
		return (0);
	if (lexer->type == PIPE)
		lexer = lexer->next;
	lcmd = malloc(sizeof(t_lcmd));
	awaiting_death(!lcmd, ms);
	lcmd->pid = 0;
	lcmd->input = 0;
	lcmd->output = 1;
	lcmd->error = 2;
	lcmd->start_lexer = lexer;
	lcmd->end_lexer = look_for_end_cmd(lexer, end_lexer);
	lcmd->cmd = 0;
	lcmd->ioe_put = 0;
	lcmd->pipe[0] = -1;
	lcmd->pipe[1] = -1;
	lcmd->next = create_lcmd(look_for_end_cmd(lexer, end_lexer), end_lexer, ms);
	return (lcmd);
}

static int	count_cmdargs(t_lexer *lexer, t_lexer *end_cmd)
{
	int	count;

	count = 0;
	while (lexer && lexer != end_cmd)
	{
		if (lexer->type == CMD || lexer->type == ARGS)
		{
			++count;
			while (lexer && (lexer->type == CMD || lexer->type == ARGS))
				lexer = lexer->next;
		}
		else
			lexer = lexer->next;
	}
	return (count);
}

char	**create_cmd(t_lexer *lexer, t_lexer *end_lexer, t_minishell *ms)
{
	t_lexer	*end_cmd;
	int		count;
	char	**cmd;

	end_cmd = look_for_end_cmd(lexer, end_lexer);
	count = count_cmdargs(lexer, end_cmd);
	cmd = malloc(sizeof(char *) * (count + 1));
	awaiting_death(!cmd, ms);
	cmd[count] = 0;
	count = 0;
	while (lexer && lexer != end_cmd)
	{
		if (lexer->type == CMD || lexer->type == ARGS)
		{
			cmd[count] = join_args(lexer);
			awaiting_death(!cmd[count++], ms);
			while (lexer && (lexer->type == CMD || lexer->type == ARGS))
				lexer = lexer->next;
		}
		else
			lexer = lexer->next;
	}
	return (cmd);
}

static int	is_there_ioe(t_lexer *lexer, t_lexer *end_lexer)
{
	static char	is_ioe[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0};
	t_lexer		*end_cmd;

	end_cmd = look_for_end_cmd(lexer, end_lexer);
	while (lexer && lexer != end_cmd)
	{
		if (is_ioe[lexer->type])
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

t_ioe_put	*create_ioeput(t_lexer *lexer, t_lexer *end_lexer, t_minishell *ms)
{
	static char	is_ioe[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0};
	t_lexer		*end_cmd;
	t_ioe_put	*ioe_put;

	if (!is_there_ioe(lexer, end_lexer))
		return (0);
	ioe_put = malloc(sizeof(t_ioe_put));
	awaiting_death(!ioe_put, ms);
	end_cmd = look_for_end_cmd(lexer, end_lexer);
	while (lexer != end_cmd)
	{
		if (is_ioe[lexer->type])
		{
			ioe_put->type = lexer->type;
			ioe_put->herename = 0;
			ioe_put->name = join_same_type(lexer->next);
			awaiting_death(!ioe_put->name, ms);
			ioe_put->next = create_ioeput(lexer->next, end_lexer, ms);
			return (ioe_put);
		}
		lexer = lexer->next;
	}
	return (0);
}
