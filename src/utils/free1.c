/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:03:34 by geudes            #+#    #+#             */
/*   Updated: 2023/07/05 08:52:08 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

void	free_ioe(t_ioe_put *ioe)
{
	t_ioe_put	*next;

	while (ioe)
	{
		next = ioe->next;
		free(ioe->name);
		free(ioe);
		ioe = next;
	}
}

void	free_cmd(t_lcmd *lcmd)
{
	t_lcmd	*next;

	while (lcmd)
	{
		next = lcmd->next;
		free_ioe(lcmd->ioe_put);
		free_split(lcmd->cmd);
		free(lcmd);
		lcmd = next;
	}
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->lcmd)
		free_cmd(node->lcmd);
	else if (node->opp)
	{
		free_node(node->opp->l_node);
		free_node(node->opp->r_node);
	}
	free(node);
}

void	free_ms(t_minishell *ms)
{
	free_lexer(ms->lexer);
	free_node(ms->tree);
	free_env(ms->env);
	kill(ms->euthanasia_pid, SIGUSR2);
}
