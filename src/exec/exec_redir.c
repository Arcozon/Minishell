/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:36:52 by nriviere          #+#    #+#             */
/*   Updated: 2023/07/16 09:37:37 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <sys/wait.h>

void	set_up_dup(t_lcmd *cmd)
{
	if (cmd->input != STDIN_FILENO)
		dup2(cmd->input, STDIN_FILENO);
	if (cmd->output != STDOUT_FILENO)
		dup2(cmd->output, STDOUT_FILENO);
	if (cmd->error != STDERR_FILENO)
		dup2(cmd->error, STDERR_FILENO);
}

void    print_cmd_noah(t_lcmd *cmd)
{
    ft_printf("\n|%s|\n", *(cmd->cmd));
    ft_printf("input:%d\noutput:%d\nerror:%d\n", cmd->input, cmd->output, cmd->error);
}

void	ft_child(t_lcmd *cmd, t_minishell *all)
{
	char	**envstrr;

	cmd->pid = fork();
	if (cmd->pid == -1)
		ft_exit_safely(all);
	else if (cmd->pid == 0)
	{
		set_up_dup(cmd);
		envstrr = t_env_to_charr(all->env);
		if (!envstrr)
			ft_exit_safely(all);
		ft_close_all_pipes(all->tree->lcmd);
		execve(*(cmd->cmd), cmd->cmd, envstrr);
		perror(*(cmd->cmd));
		ft_free_strr(envstrr);
		ft_exit_safely(all);
	}
    print_cmd_noah(cmd);
}

void	cmd_wait(t_lcmd *cmd)
{
	int	status;
	int	i;

	status = g_cmd_exit;
	i = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
		{
			if (cmd->next)
				waitpid(cmd->pid, 0, 0);
			else
				waitpid(cmd->pid, &status, 0);
			i++;
		}
		cmd = cmd->next;
	}
	if (i > 0)
		g_cmd_exit = WEXITSTATUS(status);
}
