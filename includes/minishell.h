/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:39:19 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/10 18:27:57 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_data
{
	char					*input;
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

void						ft_get_metachar(t_data *data);
void						display_usage(void);

void						ft_handle_input(void);
void						ft_exit_clean(t_data *data);
void						ft_setup_signals(void);

#endif
