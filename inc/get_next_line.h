/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 10:52:13 by nriviere          #+#    #+#             */
/*   Updated: 2023/07/05 20:23:23 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifdef MAXFD
#  undef MAXFD
# endif

# define MAXFD 1024

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>

char	*ft_strncut(char **str, int ln);
void	*ft_realloc(char **str, size_t size);
void	ft_strcat(char *str, char *str1);
char	*get_next_line(int fd);

#endif // GET_NEXT_LINE_H
