/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:38:07 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/11 18:20:08 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_minishell(t_data *data)
{
	char	*line;

	while (true)
	{
		line = readline(CLR_BLUE "minishell> " CLR_RESET);
		if (line && *line == '\0')
			continue ;
		else if (line)
		{
			add_history(line);
			if (!ft_is_closed_quotes(line))
				ft_fprintf(2, "Missing closing quote.\n");
			else
				ft_handle_input(line, data);
		}
		else
			break ;
		free(data->input);
	}
	ft_exit_clean(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (display_usage(), EXIT_FAILURE);
	(void)av;
	data.env = env;
	ft_setup_signals();
	ft_get_metachar(&data);
	ft_start_minishell(&data);
	return (EXIT_SUCCESS);
}
