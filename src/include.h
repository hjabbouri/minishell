/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hjabbour <hjabbour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:11:37 by stamim            #+#    #+#             */
/*   Updated: 2022/10/25 12:56:59 by hjabbour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <paths.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BASE 10
# define CD_NAME "cd: "
# define ENV_EMPTY_ERR "cannot work without environment variables"
# define EX_NAME "exit: "
# define EXCEEDED_ARGS " too many arguments"
# define EXP_IDE "': not a valid indentifier"
# define EXP_IDE "': not a valid indentifier"
# define EXP_TIT "export: `"
# define EXP_TIT "export: `"
# define EXPRT_PRE "declare -x "
# define EXPRT_PRE "declare -x "
# define FILE_DIR_MISS ": No such file or directory"
# define HOME_MISS "HOME not set"
# define OPR "miss use of operators\n"
# define MULTI_ARG "too many arguments"
# define NAME "minishell"
# define NOT_FOUND " not found"
# define NUM_REQ " numeric argument required"
# define OLDPWD "OLDPWD"
# define OLDPWD_MISS "OLDPWD not set"
# define PROMPT "$ "
# define PWD "PWD"
# define QUO_MISMATCH "Some quotes are not enclosed\n"
# define SEP ": "
# define SHLVL "SHLVL"
# define UNDERSCORE "_"
# define UNST_TIT "unset: `"
# define PROMPT_HRDC "> "

enum e_TYPE {
	WORD = 0,
	OPERATOR = 1,
};
enum e_OPERATOR {
	IN = 1,
	HEREDOC = 2,
	OUT = 3,
	OUT_APND = 4,
	PIPE = 5,
};

extern char	g_s[4];

typedef struct var
{
	struct var	*next;
	char		*str;
}	t_var;
typedef int	t_blt(char *args[], t_var *g_env);
typedef struct token
{
	char			*wrd;
	size_t			opr;
	size_t			type;
	struct token	*next;
}	t_token;
typedef struct pipline
{
	char	**argv;
	char	**envp;
	char	*exe;
	char	*hrdcs;
	char	*name;
	char	*paths;
	int		pipes[2];
	int		status;
	int		stdin;
	int		tty[2];
	pid_t	pid;
	size_t	count;
	size_t	opr;
	t_blt	*blt;
	t_token	*cmd;
	t_token	*head;
	t_token	*wrds;
	t_var	*e;
}	t_pipln;

bool		blank(char chr);
bool		check_exist_var_env(char *str, int idx, t_var *env);
bool		compare(const char *key, const char *cmp);
bool		ft_isalnum(char chr);
bool		ft_isalpha(char chr);
bool		ft_isdigit(char chr);
bool		open_heredoc(char *del);
bool		spec(const char *input);
char		**list2arr(t_var *env);
char		*ft_getenv(const char *key, t_var *env);
char		*ft_itoa(char *buf, int n);
char		*ft_ptrtoa(void	*nbr);
char		*ft_strchr(const char *str, int chr);
char		*ft_strdup(const char *src);
char		*ft_strjoin(char const *str1, char const *str2);
char		*ft_strndup(const char *src, size_t size);
char		*ft_substr(char const *str, unsigned int start, size_t len);
char		*get_shlvl(void);
char		*name_heredoc(char *del);
const char	*get_word(char **inp, t_var *g_env);
int			blt_cd(char *args[], t_var *env);
int			blt_echo(char *args[], t_var *env);
int			blt_env(char *args[], t_var *env);
int			blt_exit(char *args[], t_var *env);
int			blt_export(char *args[], t_var *env);
int			blt_pwd(char *args[], t_var *env);
int			blt_unset(char *args[], t_var *env);
int			clean(t_pipln *pip);
int			export_add_back_env(char *str, int idx, t_var *env);
int			ft_atoi(const char *str);
int			ft_chr(const char *str, char chr, int ret);
int			ft_strncmp(const char *str1, const char *str2, size_t n);
int			join_var_env(char *src, int idx, t_var *env);
int			lst_pipe(t_pipln pip, t_token*tkns);
int			open_files(t_pipln *pip);
int			replace_var_env(char *str, int idx, t_var *env);
int			smp_cmd_exp(t_pipln *pip);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *str);
t_blt		*find_blt(const char *blt);
t_token		*expand_token(t_token *tkn);
t_token		*ft_new_node(char *wrd, size_t opr, size_t typ);
t_token		*ft_pop_front(t_token**head);
t_token		*lex(char *inpt, t_var *g_env);
t_var		*env_dup(char **env);
t_var		*ft_new_node_env(char *str);
t_var		*get_env_node(char *key, t_var *env);
t_var		*list_create(size_t sze);
void		*ft_malloc(unsigned long size);
void		deallocate_node_env(t_var *env);
void		free_env(t_var	*env);
void		ft_env_push_back(t_var *head, t_var *new);
void		ft_lst_del_all(t_token *tkn);
void		ft_lst_del_one(t_token *tkn);
void		ft_perror(const char *cmd, char *arg, char *msg);
void		ft_push_back(t_token **head, t_token *new);
void		ft_push_front(t_token **head, t_token *new);
void		ft_strcpy(size_t start, char *dest, char const *src);
void		nw_prmpt(int _siginfo);
void		reset_signals(void);
void		exit_heredoc(int siginfo);
bool		heredoc(char *del);

#endif