/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:16:45 by geudes            #+#    #+#             */
/*   Updated: 2023/06/28 16:45:47 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_routine(int sig)
{
    if (sig ==  SIGINT)
    {
        write(1, "^C", 2)
        rl_on_new_line();
        g_cmd_exit = 130;
    }
    else if(sig == SIGQUIT)
    {
    }
}

void    sig_exec(int sig)
{
    if (sig ==  SIGINT)
    {
        g_cmd_exit = 130;
    }
    else if(sig == SIGQUIT)
    {
        g_cmd_exit = 131;
    }
}

void    set_sig_routine(void)
{
    
}

void    set_sig_exec(void)
{
    
}