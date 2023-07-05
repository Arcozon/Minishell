/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 23:50:45 by geudes            #+#    #+#             */
/*   Updated: 2023/06/30 09:35:36 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_dq(t_lexer *root, t_minishell *ms)
{
	int		i_dq;
	char	*buffer;

	buffer = root->content;
	i_dq = root->content[0] == '\"';
	while (root->content[i_dq] && root->content[i_dq] != '\"')
		i_dq++;
	root->content = ft_substr(root->content, 1, i_dq - 1);
	awaiting_death(!(root->content), ms);
	free(buffer);
	buffer = root->content;
	root->content = expand_dollar_sign(root->content, ms);
	awaiting_death(!(root->content), ms);
	free(buffer);
	root->type = TEXT;
}
