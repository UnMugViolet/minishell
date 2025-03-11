/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:38:07 by pjaguin           #+#    #+#             */
/*   Updated: 2025/02/25 15:43:23 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_minishell(void)
{
	char	*line;

	while (true)
	{
		line = readline(CLR_BLUE "minishell> " CLR_RESET);
		if (line && *line == '\0')
			continue ;
		else if (line)
		{
			ft_printf("You entered: %s\n", line);
			add_history(line);
		}
		else
			break ;
		free(line);
	}
	ft_exit_clean(line);
}

int	main(int ac, char **av, char **env)
{
	if (ac != 1)
		return (display_usage(), EXIT_FAILURE);
	(void)av;
	(void)env;
	ft_setup_signals();
	ft_start_minishell();
	return (EXIT_SUCCESS);
}
