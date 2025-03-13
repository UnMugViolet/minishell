/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:39:19 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/13 18:20:09 by unmugviolet      ###   ########.fr       */
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
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>

typedef struct s_lex
{
	size_t					type;
	void					*data;
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
}							t_data;

typedef struct sigaction	t_sigaction;

/* ---------------------------------INIT-------------------------------- */

void						ft_init_data_struct(t_data *data);

/* -------------------------------SIGNALS------------------------------- */

void						ft_setup_signals(void);

/* ---------------------------------ENV--------------------------------- */

char						*ft_get_env_variable(char **env, char *variable);

/* -------------------------------PARSING------------------------------- */

void						ft_parse_prompt(t_data *data);

/* --------------------------------LEXING------------------------------- */

void						ft_init_lex_prompt(t_data *data);

/* --------------------------------UTILS-------------------------------- */

t_lex						*ft_lexnew(size_t type, void *data);
void						ft_lexadd_back(t_lex **lex, t_lex *new);
size_t						ft_lexsize(t_lex *lex);
void						ft_print_lex(t_lex *lex); // TODO: remove for final version debug only
void						ft_free_lex(t_lex *lex);

void						ft_exit_clean(t_data *data);
void						display_usage(void);

/* --------------------------------CHECKS-------------------------------- */

bool						ft_is_closed_quotes(char *prompt);
bool						ft_is_token(char *str, t_data *data);

#endif
