/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:38:07 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/13 15:40:12 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_resolve(t_data *data)
{
	ft_init_lex_prompt(data);
	ft_parse_prompt(data);
	// ft_execute_prompt(data);
}

static void	ft_start_minishell(t_data *data)
{
	while (true)
	{
		data->prompt = readline(CYN "minishell> "BLK);
		if (data->prompt && *data->prompt == 0)
			continue ;
		else if (data->prompt)
		{
			add_history(data->prompt);
			if (!ft_is_closed_quotes(data->prompt))
				ft_fprintf(2, "Missing closing quote.\n");
			else
				ft_resolve(data);
		}
		else
			break ;
		free(data->prompt);
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
	ft_init_data_struct(&data);
	ft_start_minishell(&data);
	return (EXIT_SUCCESS);
}
