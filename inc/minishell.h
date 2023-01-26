/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:51 by geudes            #+#    #+#             */
/*   Updated: 2023/01/26 12:51:34 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT ">Minishell: "

/*--------------------Lexing-----------------------*/
# define MUST_DELETE			-3
# define UNDEFINED_TYPE			-2
# define ERROR					-1
# define TEXT					0
# define FILE_INPUT				1
# define FILE_OUTPUT			2
# define FILE_ERROR				3
# define CMD					4
# define ARGS					5
# define VAR					6
# define TEXT_SQ				7
# define TEXT_DQ				8
# define INPUT_REDIR			9
# define INPUT_HEREDOC			10
# define HEREDOC_EOF			11
# define OUTPUT_REDIR			12
# define OUTPUT_HAPPEND_REDIR	13
# define ERROR_REDIR			14
# define PIPE					15
# define AND					16
# define OR						17
# define OPEN_PAR				18
# define CLOSE_PAR				19
# define EQUAL					20
# define SPACE_					21

# define MAX_TYPE				22

typedef struct s_lexer
{
	int				type;
	char			*content;
	struct s_lexer	*next;
}	t_lexer;

t_lexer	*lexer(const char *line);
void	get_text(const char *line, int *start, t_lexer **root);
void	change_text(t_lexer *root);

/*--------------------Parsing-----------------------*/
typedef struct s_cmd
{
	char			**cmd;
	int				input;
	int				output;
	int				e_output;
	struct s_cmd	*next_cmd;
}	t_cmd;

char	**get_cmd(char *line);
t_cmd	*parsing_t_cmd(char *cmd, int input, int output, int e_output);
void	aff_lexer(t_lexer *root);

/*---------------------Built ins----------------------*/
void	_echo(char **args);
char	*_pwd(void);
int		_cd(char *path);
void	_env(char **_env);
void	__exit(void);

int		check_built_ins(char *line, char **_cmd);

/*-----------------------Utils------------------------*/
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
