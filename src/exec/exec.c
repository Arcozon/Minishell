/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 09:55:29 by geudes            #+#    #+#             */
/*   Updated: 2023/07/20 21:14:42 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_is_std_fd(int fd)
{
	return (fd == STDIN_FILENO || fd == STDOUT_FILENO || fd == STDERR_FILENO);
}

void	ft_exec(t_minishell *all, t_lcmd *cmd)
{
	char	**path;
	int		status;

	path = ft_get_path(all->env);
	status = ft_get_working_path(path, &(*(cmd->cmd)));
	ft_free_strr(path);
	if (status == 0)
	{
		status = ft_is_file(*(cmd->cmd));
		if (status == 0)
			ft_child(cmd, all);
	}
	else if (status == 3)
	{
		ft_putstr_to_fd(2, *(cmd->cmd));
		ft_putstr_to_fd(2, ": command not found\n");
	}
	if (status == -1)
	{
		ft_putstr_fd(2, PROMPTERR);
		perror(*(cmd->cmd));
	}
	if (status != 0)
		cmd->pid = -747;
}

void	ft_chain_exec(t_minishell *all, t_lcmd *cmd, int *lastpipe, int status)
{
	if (*lastpipe != -1)
		if (ft_is_std_fd(cmd->input))
			cmd->input = *lastpipe;
	if (cmd->next)
	{
		if (pipe(cmd->pipe) == -1)
			ft_exit_safely(all);
		if (ft_is_std_fd(cmd->output))
			cmd->output = cmd->pipe[1];
		*lastpipe = cmd->pipe[0];
	}
	if (status == 0 && !ft_is_builtin(cmd, all))
		ft_exec(all, cmd);
}

int	process_cmd(t_minishell *all, t_lcmd *cmd)
{
	int		lastdeeznuts;
	t_lcmd	*tmp;
	int		status;

	lastdeeznuts = -1;
	tmp = cmd;
	while (tmp)
		tmp = (expand_cmd_ioe(tmp, all), tmp->next);
	tmp = cmd;
	while (tmp)
	{
		status = process_file(tmp, 0);
		if (status == 2)
			return (1);
		if (status == 1)
			g_cmd_exit = 1;
		ft_chain_exec(all, tmp, &lastdeeznuts, status);
		tmp = tmp->next;
	}
	ft_close_all_files(cmd);
	cmd_wait(cmd);
	here_unlink(cmd);
	return (0);
}

int	process_tree(t_minishell *all, t_node *tree)
{
	if (!tree)
		return (1);
	if (tree->lcmd && !tree->opp)
	{
		if (process_cmd(all, tree->lcmd) == 1)
			return (1);
	}
	else if (!tree->lcmd && tree->opp)
	{
		if (process_tree(all, tree->opp->l_node) == 1)
			return (1);
		if (tree->opp->logical_opp == AND)
		{
			if (!g_cmd_exit)
				if (process_tree(all, tree->opp->r_node) == 1)
					return (1);
		}
		else if (tree->opp->logical_opp == OR)
			if (g_cmd_exit)
				if (process_tree(all, tree->opp->r_node) == 1)
					return (1);
	}
	else
		return (1);
	return (0);
}
