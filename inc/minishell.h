/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:51 by geudes            #+#    #+#             */
/*   Updated: 2023/02/09 04:38:55 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT ">Minishell:"

//ls | xargs -I var find var -name "PATERN" -not -path '* /\.*' | grep -v /
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
# define TEXT_SQ				6
# define TEXT_DQ				7
# define INPUT_REDIR			8
# define INPUT_HEREDOC			9
# define HEREDOC_EOF			10
# define OUTPUT_REDIR			11
# define OUTPUT_HAPPEND_REDIR	12
# define ERROR_REDIR			13
# define PIPE					14
# define AND					15
# define OR						16
# define OPEN_PAR				17
# define CLOSE_PAR				18
# define SPACE_					19

# define MAX_TYPE				20

/*-------------------Environement-------------------*/
typedef struct s_env
{
	char			*var_name;
	char			*content;
	struct s_env	*next;
}	t_env;

t_env	*cpy_env(char **_env);

/*---------------------Built ins----------------------*/
int		bi_echo(char **av, t_env *env);
int		bi_pwd(char **av, t_env *env);
int		bi_cd(char **av, t_env *env);
int		bi_env(char **av, t_env *env);
int		bi_export(char **av, t_env **env);
void	bi_exit(void);

char	*get_pwd(void);
t_env	*new_env(char *var);
void	env_addback(t_env **root, t_env *new);

/*-----------------------Lexer----------------------*/
typedef struct s_lexer
{
	int				type;
	char			*content;
	struct s_lexer	*next;
}	t_lexer;

t_lexer	*lexer(const char *line);
void	get_text(const char *line, int *start, t_lexer **root);
void	change_text(t_lexer *root);
void	aff_lexer(t_lexer *root);
void	change_space(t_lexer **root);
void	change_text(t_lexer *root);
void	change_text_into_cmd_args(t_lexer *root);

/*---------------------Syntax-----------------------*/
int		check_parenthesis(t_lexer *root);
int		check_special(t_lexer *root);
int		syntax(t_lexer *root);

/*--------------------Parsing-----------------------*/

/*-----------------------Utils------------------------*/
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_with_slash(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
