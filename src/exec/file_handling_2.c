/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:37:01 by nriviere          #+#    #+#             */
/*   Updated: 2023/07/15 18:37:38 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	here_unlink(t_lcmd *cmd)
{
	t_ioe_put	*tmp;

	while (cmd)
	{
		tmp = cmd->ioe_put;
		while (tmp)
		{
			if (tmp->type == INPUT_HEREDOC && tmp->herename != 0)
				tmp->herename = (unlink(tmp->herename),
						free(tmp->herename), (char *)0);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

void	ft_close_all_files(t_lcmd *cmd)
{
	while (cmd)
	{
		if (cmd->input > 2)
			close(cmd->input);
		if (cmd->output > 2)
			close(cmd->output);
		if (cmd->error > 2)
			close(cmd->error);
		if (cmd->pipe[0] != -1)
			close(cmd->pipe[0]);
		if (cmd->pipe[1] != -1)
			close(cmd->pipe[1]);
		cmd = cmd->next;
	}
}

void	ft_close_all_pipes(t_lcmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe[0] != -1)
			close(cmd->pipe[0]);
		if (cmd->pipe[1] != -1)
			close(cmd->pipe[1]);
		cmd = cmd->next;
	}
}
