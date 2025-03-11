/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:39:19 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/11 17:53:22 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "ft_fprintf.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>

typedef struct s_data
{
	char					**input;
	int						in_fd;
	int						out_fd;
	int						cmd_count;
	int						pipefd[2];
	int						here_doc;
	char					**env;
	char					**paths;
	char					*cmd_path;
	char					**current_cmd;
	char					**metachar;
}							t_data;

typedef struct sigaction	t_sigaction;

# define CLR_RESET "\033[0m"
# define CLR_BLUE "\033[34m"
# define DEFAULT_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:\
/sbin:/bin"
# define METACHAR "< > << >> | || & && \" \' $"

void						ft_get_metachar(t_data *data);
char						*ft_get_env_variable(char **env, char *variable);
void						display_usage(void);

void						ft_handle_input(char *line, t_data *data);
void						ft_exit_clean(t_data *data);
void						ft_setup_signals(void);
int							ft_is_closed_quotes(char *input);
void						ft_get_metachar(t_data *data);


#endif
