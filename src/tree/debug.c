/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 06:07:23 by geudes            #+#    #+#             */
/*   Updated: 2023/06/08 08:56:55 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_tree(t_node *node, int count)
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
            // print_opp(node->opp, count + 1);
        }
    }
    printf("End of Node %d: %p\n", count, node);
    printf("-------------\n");
}

void    print_lcmd(t_lcmd *lcmd, int count)
{
    int i;

    i = -1;
    printf("Commande %d: %p\n",count,lcmd);
    while(lcmd->cmd[++i])
        printf("%s ", lcmd->cmd[i]);
    printf("\n");
    print_ioeput(lcmd->ioe_put);
    if (lcmd->next)
    {
        printf("Pipe\n");
        print_lcmd(lcmd->next, count + 1);
    }
}

void    print_ioeput(t_ioe_put *ioeput)
{
    static char *trad[] = {"Error", "Error", "Error", "Error", "Error",
        "Error", "Error", "Error", "<", "<<", "Error", ">", ">>", "2>",
        "Error", "Error", "Error", "Error", "Error", "Error"};
    while (ioeput)
    {
        printf("  %s%s\n", trad[ioeput->type], ioeput->name);
        ioeput =ioeput->next;
    }
}