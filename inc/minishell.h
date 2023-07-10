/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geudes <geudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:51 by geudes            #+#    #+#             */
/*   Updated: 2023/07/10 14:47:07 by geudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
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

/*--------------------WTF Binary Tree-----------------------*/
typedef struct s_ioe_put
{
	int					type;
	char				*herename;
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
	int                 pipe[2];
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
	t_env				*env;
	t_lexer				*lexer;
	t_node				*tree;
	char				*line;
	int					euthanasia_pid;
}						t_minishell;

void					lexer_add_back(t_lexer **root, t_lexer *new);
t_lexer					*lexer_new(int type, char *content);
t_lexer					*lexer(const char *line, t_minishell *ms);
void					get_text(const char *line, int *start, t_lexer **root);
void					aff_lexer(t_lexer *root, t_lexer *end_lexer);
void					change_space(t_lexer **root);
void					change_text(t_lexer *root, t_lexer *end_lexer);
void					change_text_into_cmd_args(t_lexer *root,
							t_lexer *end_lexer);
void					free_lexer(t_lexer *root);

//ls | xargs -I var find var -name "PATERN" -not -path '* /\.*' | grep -v /
/*---------------------Expand-----------------------*/
void					expand_sq(t_lexer *root, t_minishell *ms);
void					expand_dq(t_lexer *root, t_minishell *ms);
t_lexer					**expand_text(t_lexer **root, t_minishell *ms);
t_lexer					*expand_wc_v2(char *patern, t_minishell *ms);
char					*expand_dollar_sign(char *text, t_minishell *ms);
void					expand_cmd_ioe(t_lcmd *lcmd, t_minishell *ms);

/*---------------------Syntax-----------------------*/
int						check_parenthesis(t_lexer *root);
int						check_special(t_lexer *root);
int						check_quote(t_lexer *root);
int						check_cmd(t_lexer *root);
int						syntax(t_lexer *root);

t_node					*create_node(t_lexer *lexer, t_lexer *end_lexer,
							t_minishell *ms);

t_opp					*create_opp(t_lexer *lexer, t_lexer *end_lexer,
							t_minishell *ms);

t_lcmd					*create_lcmd(t_lexer *lexer, t_lexer *end_lexer,
							t_minishell *ms);
char					**create_cmd(t_lexer *lexer, t_lexer *end_lexer,
							t_minishell *ms);
t_ioe_put				*create_ioeput(t_lexer *lexer, t_lexer *end_lexer,
							t_minishell *ms);

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
int						bi_echo(t_lcmd *lcmd, t_minishell *ms);
int						bi_pwd(t_lcmd *lcmd, t_minishell *ms);
int						bi_cd(t_lcmd *lcmd, t_minishell *ms);
int						bi_env(t_lcmd *lcmd, t_minishell *ms);
int						bi_export(t_lcmd *lcmd, t_minishell *ms);
int						bi_unset(t_lcmd *lcmd, t_minishell *ms);
int						bi_clear(t_lcmd *lcmd, t_minishell *ms);
int						bi_owo(t_lcmd *lcmd, t_minishell *ms);
int						bi_which(t_lcmd *lcmd, t_minishell *ms);
int						bi_exit(t_lcmd *lcmd, t_minishell *ms);

char					*get_pwd(void);
t_env					*new_env(char *var);
void					env_addback(t_env **root, t_env *new);

int						ft_is_builtin(t_lcmd *cmd, t_minishell *all);
int	                    process_tree(t_minishell *all, t_node *tree);
void					set_up_dup(t_lcmd *cmd);
char					**t_env_to_charr(t_env *env);
void					ft_free_strr(char **str);

/*----------------------Utils-----------------------*/
char					*ft_strdup(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strjoin_with_slash(char const *s1, char const *s2);
int	                    ft_strlen(char *str);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
char					*join_args(t_lexer *lexer);
void					my_bbsort(char **tab);
void					*ms_calloc(unsigned int to_malloc, t_minishell *ms);
char					*strnrand(int len);
int						ft_strcmp(const char *str1, const char *str2);
char					**ft_split(char const *s, char c);
int	                    ft_putstr_fd(int fd, char *str);
int                     heredoc(t_lcmd *cmd, t_ioe_put *ioe, int *ostatus);
int	                    ft_open_file(char *name, int *fd, int oflag, int mode);

/*----------------------Signal-----------------------*/
void					set_sig_exec(void);
void					set_sig_routine(void);

/*---------------------Free--------------------------*/
void					free_ms(t_minishell *ms);
void					free_node(t_node *node);
void					free_cmd(t_lcmd *lcmd);
void					free_ioe(t_ioe_put *ioe);
void					free_split(char **split);
void					free_env(t_env *env);
void					free_lexer(t_lexer *root);
int						euthanasia(void);
void					awaiting_death(int test, t_minishell *ms);
void                    ft_exit_safely(t_minishell *all);
void                    ft_close_all_files(t_lcmd *cmd);
void                    ft_close_all_pipes(t_lcmd *cmd);
void	                here_unlink(t_lcmd *cmd);

#endif
