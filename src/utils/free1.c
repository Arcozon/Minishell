/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 12:03:34 by geudes            #+#    #+#             */
/*   Updated: 2023/06/24 12:13:16 by geudes           ###   ########.fr       */
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

void	free_ioe(t_ioeput *ioe)
{
	if (!ioe)
		return ;
	if (ioe->next)
		free_ioe(ioe->next);
	free(ioe->name);
	free(ioe);
}

void	free_cmd(t_lcmd *lcmd)
{
	if (!lcmd)
		return ;
	if (lcmd->next)
		free_cmd(lcmd->next);
	free_ioe(lcmd->ioeput);
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->cmd)
		free_cmd(node->cmd);
	else if (node->opp)
	{
		free_node(node->opp->lnode);
		free_node(node->opp->rnode);
	}
	free(node);
}

void	free_ms(t_minishell ms)
{
	free_lexer(ms.lexer);
	free_node(ms.tree);
	free_env(ms.env);
}
