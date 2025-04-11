/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:52:21 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/04/11 09:21:25 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Disable the echo of CTRL command in the terminal
	by setting the ECHOCTL flag to 0
	@param void
	@return void
*/
static void	ft_disable_echoctl(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

/*
	Handle the type of signal received and act accordingly
	@param int signal
	@return void
*/
static void	ft_handle_signal(int signal)
{
	printf("exit heredoc: %d\n", g_in_heredoc);
	if (g_in_heredoc)
	{
		printf("Been here\n");
		if (signal == SIGINT || signal == SIGCHLD || signal == SIGTERM)
			ft_fprintf(STDOUT_FILENO, "\n");
		return ;
	}
	if (!g_in_heredoc && (signal == SIGINT || signal == SIGCHLD))
	{
		printf("Been there\n");
		ft_fprintf(STDOUT_FILENO, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGTERM)
		ft_exit_clean(NULL, 1, false);
}

/*
	Setup the signals to be handled by the shell,
	use the `sa` structure to set the flags and the handler
	@param void
	@return void
*/
void	ft_setup_signals(void)
{
	t_sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = ft_handle_signal;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
	ft_disable_echoctl();
}
