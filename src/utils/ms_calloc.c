/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 11:46:49 by geudes            #+#    #+#             */
/*   Updated: 2023/06/24 12:10:35 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ms_calloc(unsigned int to_malloc, t_minishell ms)
{
	unsigned int	i;
	void			*res;
	char			*cres;

	res = malloc(to_malloc);
	if (!res)
	{
		write(2, "Mallocaca\n", 10);
		free_ms(ms);
		exit(1);
	}
	cres = (char *)res;
	i = -1;
	while (++i < to_malloc)
		cres[i] = 0;
	return (res);
}
