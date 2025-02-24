/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:52:21 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/02/24 16:06:45 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static void ft_disable_echoctl(void)
{
    struct termios term;
    
    if (tcgetattr(STDIN_FILENO, &term) == 0)
    {
        term.c_lflag &= ~ECHOCTL;
        tcsetattr(STDIN_FILENO, TCSANOW, &term);
    }
}

static void ft_handle_signal(int signal)
{
    if (signal == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
	else if (signal == SIGTERM)
		ft_exit_clean(NULL);
}

void ft_setup_signals(void)
{
    t_sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = ft_handle_signal;
    sigaction(SIGINT, &sa, NULL);
    sa.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa, NULL);
	ft_disable_echoctl();
}
