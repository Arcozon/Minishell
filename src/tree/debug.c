/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:07:23 by geudes            #+#    #+#             */
/*   Updated: 2023/06/15 00:16:13 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_node *node, int count)
{
	printf("-------------\n");
	printf("Node %d: %p ", count, node);
	if (node)
	{
		if (node->lcmd)
		{
			printf("Liste Commande\n");
			print_lcmd(node->lcmd, count + 1);
		}
		else
		{
			printf("Logical opp\n");
			print_opp(node->opp, count + 1);
		}
	}
	printf("End of Node %d: %p\n", count, node);
	printf("-------------\n");
}

void	print_opp(t_opp *opp, int count)
{
	static char	*trad[] = {"OR", "AND"};

	printf("############################\n");
	printf("OPP %d: %s :%p\n", count, trad[opp->logical_opp == AND], opp);
	printf(" --L Node %d: %p\n", count + 1, opp->l_node);
	print_tree(opp->l_node, count + 1);
	printf(" --R Node %d: %p\n", count + 2, opp->r_node);
	print_tree(opp->r_node, count + 2);
	printf("############################\n");
}

void	print_lcmd(t_lcmd *lcmd, int count)
{
	int	i;

	i = -1;
	printf("Commande %d: %p\n", count, lcmd);
	while (lcmd->cmd[++i])
		printf("%d:%s,", i, lcmd->cmd[i]);
	printf("\n");
	print_ioeput(lcmd->ioe_put);
	if (lcmd->next)
	{
		printf("Pipe\n");
		print_lcmd(lcmd->next, count + 1);
	}
}

void	print_ioeput(t_ioe_put *ioeput)
{
	static char *trad[] = {"Error", "Error", "Error", "Error", "Error", "Error",
		"Error", "Error", "<", "<<", "Error", ">", ">>", "2>", "Error", "Error",
		"Error", "Error", "Error", "Error"};

	while (ioeput)
	{
		printf("  %s%s\n", trad[ioeput->type], ioeput->name);
		ioeput = ioeput->next;
	}
}
