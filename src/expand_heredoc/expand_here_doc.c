/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 15:22:31 by geudes            #+#    #+#             */
/*   Updated: 2023/07/10 15:29:01 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_hd(t_ioe_put *ioe, t_minishell *ms)
{
	int	my_hd;
    (void)my_hd;
    (void)ioe;
    (void)ms;

	//gnl a line
	//use expand_dollarsign on line like this

	//buffer = line;
	//line = expand_dollar_sign(line, ms);
	//free(buffer);

	//write to new here doc
	//close old here doc
} 
