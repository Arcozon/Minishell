/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriviere <nriviere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 18:43:16 by nriviere          #+#    #+#             */
/*   Updated: 2023/07/15 18:43:17 by nriviere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_t;

	s_t = s;
	while (n--)
		s_t[n] = c;
	return (s);
}

void	*ft_calloc(size_t nmemb, size_t n)
{
	void	*ptr;

	if (!n)
		return (malloc(0));
	if (nmemb * n / n != nmemb)
		return (0);
	ptr = malloc(nmemb * n);
	if (ptr)
		ft_memset(ptr, 0, nmemb * n);
	return (ptr);
}

void	ft_free_strr(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
	}
	free(str);
}
