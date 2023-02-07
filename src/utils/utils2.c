/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:39:25 by geudes            #+#    #+#             */
/*   Updated: 2023/02/06 08:41:58 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_with_slash(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		iptr;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = 0;
	iptr = 0;
	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1 + 1) * sizeof(char));
	if (ptr == 0)
		return (0);
	while (s1[i])
		ptr[iptr++] = s1[i++];
	ptr[iptr++] = '/';
	i = 0;
	while (s2[i])
		ptr[iptr++] = s2[i++];
	ptr[iptr] = '\0';
	return (ptr);
}
