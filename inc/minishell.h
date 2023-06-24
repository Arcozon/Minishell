/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:51 by geudes            #+#    #+#             */
/*   Updated: 2023/06/24 12:48:37 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PROMPT ">Minishell:"
# define RETURN_VAR "?"

/*--------------------Lexing-----------------------*/
# define MUST_DELETE -3
# define UNDEFINED_TYPE -2
# define ERROR -1
# define TEXT 0
# define FILE_INPUT 1
# define FILE_OUTPUT 2
# define FILE_ERROR 3
# define CMD 4
# define ARGS 5
# define TEXT_SQ 6
# define TEXT_DQ 7
# define INPUT_REDIR 8
# define INPUT_HEREDOC 9
# define HEREDOC_EOF 10
# define OUTPUT_REDIR 11
# define OUTPUT_HAPPEND_REDIR 12
# define ERROR_REDIR 13
# define PIPE 14
# define AND 15
# define OR 16
# define OPEN_PAR 17
# define CLOSE_PAR 18
# define SPACE_ 19

# define MAX_TYPE 20

extern int				g_cmd_exit;

/*-------------------Environement-------------------*/
typedef struct s_env
{
	char				*var_name;
	char				*content;
	struct s_env		*next;
}						t_env;

t_env					*cpy_env(char **_env);

/*-----------------------Lexer----------------------*/
typedef struct s_lexer
{
	int					type;
	char				*content;
	struct s_lexer		*next;
}						t_lexer;

void					lexer_add_back(t_lexer **root, t_lexer *new);
t_lexer					*lexer_new(int type, char *content);
t_lexer					*lexer(const char *line);
void					get_text(const char *line, int *start, t_lexer **root);
void					aff_lexer(t_lexer *root);
void					change_space(t_lexer **root);
void					change_text(t_lexer *root, t_lexer *end_lexer);
void					change_text_into_cmd_args(t_lexer *root,
							t_lexer *end_lexer);
void					free_lexer(t_lexer *root);

//ls | xargs -I var find var -name "PATERN" -not -path '* /\.*' | grep -v /
/*---------------------Expand-----------------------*/
void					expand_me_onee_chan(t_lexer **root, t_env *env);
void					expand_sq(t_lexer *root, t_env *env);
void					expand_dq(t_lexer *root, t_env *env);
t_lexer					**expand_text(t_lexer **root, t_env *env);
t_lexer					*expand_wc_v2(char *patern);
char					*expand_var_name(char *text, int *start, t_env *env);
char					*expand_dollar_sign(char *text, t_env *env);

/*---------------------Syntax-----------------------*/
int						check_parenthesis(t_lexer *root);
int						check_special(t_lexer *root);
int						check_quote(t_lexer *root);
int						check_cmd(t_lexer *root);
int						syntax(t_lexer *root);

/*--------------------WTF Binary Tree-----------------------*/
typedef struct s_ioe_put
{
	int					type;
	char				*name;
	struct s_ioe_put	*next;
}						t_ioe_put;

typedef struct s_lcmd
{
	int					input;
	int					output;
	int					error;
	t_ioe_put			*ioe_put;
	int					pid;
	t_lexer				*start_lexer;
	t_lexer				*end_lexer;
	char				**cmd;
	struct s_lcmd		*next;
}						t_lcmd;

struct					s_node;

typedef struct s_opp
{
	int					logical_opp;
	struct s_node		*r_node;
	struct s_node		*l_node;
}						t_opp;

typedef struct s_node
{
	t_lcmd				*lcmd;
	t_opp				*opp;
}						t_node;

typedef struct s_minishell
{
	t_lexer	*lexer;
	t_node	*tree;
	t_env	*env;
}	t_minishell;

t_node					*create_node(t_lexer *lexer, t_lexer *end_lexer);

t_opp					*create_opp(t_lexer *lexer, t_lexer *end_lexer);

t_lcmd					*create_lcmd(t_lexer *lexer, t_lexer *end_lexer);
char					**create_cmd(t_lexer *lexer, t_lexer *end_lexer);
t_ioe_put				*create_ioeput(t_lexer *lexer, t_lexer *end_lexer);

t_lexer					*look_for_first_opp(t_lexer *lexer, t_lexer *end_lexer);
t_lexer					*look_for_mid_opp(t_lexer *lexer, t_lexer *end_lexer);
t_lexer					*look_for_last_opp(t_lexer *lexer, t_lexer *end_lexer);
char					*join_same_type(t_lexer *lexer);
char					*join_args(t_lexer *lexer);
t_lexer					*look_for_pipe(t_lexer *lexer, t_lexer *end_lexer);
t_lexer					*look_for_end_cmd(t_lexer *lexer, t_lexer *end_lexer);

void					print_tree(t_node *node, int count);
void					print_opp(t_opp *opp, int count);
void					print_lcmd(t_lcmd *lcmd, int count);
void					print_ioeput(t_ioe_put *ioeput);

/*---------------------Built ins----------------------*/
int						bi_echo(t_lcmd *lcmd, t_env *env);
int						bi_pwd(t_lcmd *lcmd, t_env **env);
int						bi_cd(t_lcmd *lcmd, t_env *env);
int						bi_env(t_lcmd *lcmd, t_env *env);
int						bi_export(t_lcmd *lcmd, t_env **env);
int						bi_unset(t_lcmd *lcmd, t_env **env);
int						owo(t_lcmd *lcmd, t_env *env);
void					bi_exit(void);

char					*get_pwd(void);
t_env					*new_env(char *var);
void					env_addback(t_env **root, t_env *new);


int						ft_is_builtin(t_lcmd *cmd, t_env *env);
void					process_tree(t_node *tree, t_env *envdeeznuts);

/*----------------------Utils-----------------------*/
char					*ft_strdup(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin_with_slash(char const *s1, char const *s2);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*join_args(t_lexer *lexer);
void					my_bbsort(char **tab);
void					*ms_calloc(unsigned int to_malloc, t_minishell ms);
char	*strnrand(int len);

/*---------------------Free--------------------------*/
void	free_ms(t_minishell ms);
void	free_node(t_node *node);
void	free_cmd(t_lcmd *lcmd);
void	free_ioe(t_ioe_put *ioe);
void	free_split(char **split);
void	free_env(t_env *env);
void	free_lexer(t_lexer *root);


#endif
