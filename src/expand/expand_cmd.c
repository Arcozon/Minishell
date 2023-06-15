/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 05:02:04 by geudes            #+#    #+#             */
/*   Updated: 2023/06/15 05:08:39 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minshell.h"

char	**fucking_expand_cmd(char **cmd, t_env *env)
{
	char	*buff;
	int		i;
	int		j;
	int		what_did_i_find;

	i = -1;
	while (cmd[++i])
	{
		j = -1;
		what_did_i_find = 0;
		buff = cmd[i];
		while (cmd[i][++j])
			what_did_i_find |= cmd[i][j] == '$' + 2 * cmd[i][j] == '*';
		if (what_did_i_find & 1)
			cmd[i] = expand_dollar_sign(cmd[i], env);
		else if (what_did_i_find & 2)
			cmd[i] = wildcardv2(cmd[i]);
		if (what_did_i_find)
			free(buff);
	}
}
