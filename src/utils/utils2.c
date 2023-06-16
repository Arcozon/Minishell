/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 08:39:25 by geudes            #+#    #+#             */
/*   Updated: 2023/06/16 19:23:38 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_strjoin_with_slash(char const *s1, char const *s2)
// {
// 	char	*ptr;
// 	int		i;
// 	int		iptr;

// 	if (!s1 && !s2)
// 		return (0);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	i = 0;
// 	iptr = 0;
// 	ptr = malloc((ft_strlen(s1) + ft_strlen(s2) + 1 + 1) * sizeof(char));
// 	if (ptr == 0)
// 		return (0);
// 	while (s1[i])
// 		ptr[iptr++] = s1[i++];
// 	ptr[iptr++] = '/';
// 	i = 0;
// 	while (s2[i])
// 		ptr[iptr++] = s2[i++];
// 	ptr[iptr] = '\0';
// 	return (ptr);
// }

static const int	g_trad[128] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
	21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
	39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64, 75, 77, 79, 81, 83, 85, 87, 89, 91, 93,
	95, 97, 99, 101, 103, 105, 107, 109, 111, 113, 115, 117, 119, 121, 123,
	125, 65, 66, 67, 68, 69, 70, 76, 78, 80, 82, 84, 86, 88, 90, 92, 94,
	96, 98, 100, 102, 104, 106, 108, 110, 112, 114, 116, 118, 120, 122, 124,
	126, 71, 72, 73, 74, 127};

static int	ft_strcmpup1low2(const char *s1, const char *s2)
{
	size_t			i;

	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (g_trad[(int)s1[i]] - g_trad[(int)s2[i]]);
		i++;
	}
	if ((s1[i] || s2[i]))
		return (g_trad[(int)s1[i]] - g_trad[(int)s2[i]]);
	return (0);
}

void	my_bbsort(char **tab)
{
	char	*buff;
	int		i;
	int		j;

	i = 0;
	while (tab[i])
	{
		j = i + 1;
		while (tab[j])
		{
			if (ft_strcmpup1low2(tab[i], tab[j]) < 0)
			{
				buff = tab[j];
				tab[j] = tab[i];
				tab[i] = buff;
			}
			j++;
		}
		i++;
	}
}
