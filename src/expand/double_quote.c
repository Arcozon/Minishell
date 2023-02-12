/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:50:45 by geudes            #+#    #+#             */
/*   Updated: 2023/02/12 06:06:55 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_dq(t_lexer *root, t_env *env)
{
	int		i_dq;
	char	*buffer;

	(void)env;
	buffer = root->content;
	i_dq = root->content[0] == '\"';
	while (root->content[i_dq] && root->content[i_dq] != '\"')
		i_dq++;
	root->content = ft_substr(root->content, 1, i_dq - 1);
	free(buffer);
	buffer = root->content;
	root->content = expand_dollar_sign(root->content, env);
	free(buffer);
	root->type = TEXT;
}
