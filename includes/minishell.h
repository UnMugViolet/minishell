/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:39:19 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/12 14:54:13 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct	s_quotes
{
	bool		in_sgl;
	char		single;
	bool		in_dbl;
	char		dbl;
}				t_quotes;

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
	t_quotes				quotes;
	size_t					lex_size;
}							t_data;

typedef struct sigaction	t_sigaction;

# define CLR_RESET "\033[0m"
# define CLR_BLUE "\033[34m"
# define METACHAR "< > << >> | || & && $"
# define DEFAULT_PATH \
	"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:\
/sbin:/bin"

/* ---------------------------------INIT-------------------------------- */

void						ft_init_data_struct(t_data *data);
void						ft_init_quote_struct(t_quotes *quotes);

/* -------------------------------SIGNALS------------------------------- */

void						ft_setup_signals(void);

/* ---------------------------------ENV--------------------------------- */

char						*ft_get_env_variable(char **env, char *variable);

/* -------------------------------PARSING------------------------------- */

void						ft_handle_input(char *line, t_data *data);

/* --------------------------------LEXING------------------------------- */

void						ft_init_lex_prompt(t_data *data);

/* --------------------------------UTILS-------------------------------- */

void						ft_exit_clean(t_data *data);
void						display_usage(void);

/* --------------------------------CHECKS-------------------------------- */

bool						ft_is_closed_quotes(char *prompt);
bool						ft_is_token(char *str, t_data *data);

#endif
