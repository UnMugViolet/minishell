/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:39:19 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/31 11:14:27 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dictionnary.h"
# include "ft_fprintf.h"
# include "ft_printf.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>

typedef struct s_exec
{
	char					**cmd;
	char					*full_cmd;
	char					**infile;
	char					**outfile;
	size_t					type;
	struct s_exec			*next;
	struct s_exec			*prev;
}							t_exec;

typedef struct s_lex
{
	size_t					type;
	char					*content;
	struct s_lex			*next;
}							t_lex;

typedef struct s_data
{
	char					*prompt;
	char					**env;
	char					**paths;
	char					**metachar;
	t_lex					*lex;
	size_t					lex_size;
	int						pipe_fd[2];
	int						in_fd;
	int						out_fd;
	char					*curr_dir;
	char					*last_exit_value;
	t_exec					*exec;
}							t_data;

typedef struct sigaction	t_sigaction;

/* ---------------------------------INIT-------------------------------- */

void						ft_init_data_struct(t_data *data, char **env);

/* -------------------------------SIGNALS------------------------------- */

void						ft_setup_signals(void);

/* ---------------------------------ENV--------------------------------- */

void						ft_replace_env_variable(t_data *data);
char						*ft_get_env_var_name(char *str);
char						*ft_get_associated_env_value(t_data *data,
								char *variable);
void						ft_delete_env_var(t_data *data, char *var);
void						ft_create_env_var(t_data *data, char *str);
void						ft_update_env_var(t_data *data, char *variable,
								char *new_value);
char						*ft_get_env_var_adress(t_data *data,
								char *variable);

/* -------------------------------PARSING------------------------------- */

void						ft_parse_prompt(t_data *data);
void						ft_get_heredocs(t_data *data);
void						ft_get_outfile(t_data *data);
void						ft_get_pipes(t_data *data);
void						ft_get_infiles(t_data *data);
void						ft_get_commands(t_data *data);
void						ft_create_exec_conditionaly(t_data *data, char *cmd,
								size_t type);

/* --------------------------------LEXING------------------------------- */

void						ft_init_prompt_lexing(t_data *data);

/* --------------------------------UTILS-------------------------------- */

void						ft_get_current_dir(t_data *data);

t_lex						*ft_lexnew(size_t type, char *content);
void						ft_lexadd_back(t_lex **lex, t_lex *new);
size_t						ft_lexsize(t_lex *lex);
void						ft_lex_del_content(t_lex *lex);

t_exec						*ft_exec_new(char **cmd, char *path, size_t type);
void						ft_exec_add_back(t_exec **exec, t_exec *new);

char						*ft_str_substitute(char *str, t_data *data);
char						*ft_get_last_word(t_lex *lex);
void						ft_add_str_array(char ***array, char *str);

void						ft_update_last_exit_value(t_data *data, int value);

/* --------------------------------CHECKS-------------------------------- */

bool						ft_is_correct_input(char *prompt);
bool						ft_is_closed_quotes(char *prompt);
bool						ft_is_token(char *str, t_data *data);
bool						ft_is_env_var(char *str);
bool						ft_is_correct_token(t_lex *lex, char **metachar);
bool						ft_is_metacharset(char *str, char **metacharset);
char						*ft_single_token(t_lex *lex, char **metachar);

/* -------------------------------BUILTINS------------------------------- */

bool						ft_check_exec_builtins(t_data *data, char **cmd);
int							ft_cd(t_data *data, char **cmd);

/* ---------------------------------PATH--------------------------------- */

char						*ft_get_path_for_cmd(t_data *data, char *cmd);

/* ---------------------------------EXEC--------------------------------- */

void						ft_execute_prompt(t_data *data);
void						ft_get_first_command(t_data *data, size_t *i);
void						ft_exec_child(t_data *data, t_exec *exec);
void						ft_setup_pipe(t_data *data, int is_pipe,
								int is_child);
void						ft_wait_and_update_status(t_data *data, pid_t pid);

/* --------------------------------ERRORS-------------------------------- */

void						ft_exit_error(t_data *data, char *str, int code);
void						ft_exit_clean(t_data *data, int error_code);
void						ft_close_fds(t_data *data);
void						display_usage(void);

/* ---------------------------------FREE--------------------------------- */

void						ft_free_lex(t_lex *lex);
void						ft_free_exec(t_exec *exec);

/* -------------------------PRINTS TO-DO REMOVE LATER---------------------- */

void						ft_print_lex(t_lex *lex);
void						ft_print_exec(t_exec *exec);

#endif
