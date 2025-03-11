/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:38:07 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/11 17:20:26 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_metachar(t_data *data)
{
	char const	*metachar = "< > << >> | || & && \" \' $";

	data->metachar = ft_split(metachar, ' ');
}

void	ft_start_minishell(t_data *data)
{
	ft_get_metachar(data);
	while (true)
	{
		data->input = readline(CLR_BLUE "minishell> " CLR_RESET);
		if (data->input && *data->input == '\0')
			continue ;
		else if (data->input)
		{
			add_history(data->input);
			if (!ft_is_closed_quotes(data->input))
				ft_fprintf(2, "Missing closing quote.\n");
			else
			{
				if (data->input[0] == '$')
					data->input = ft_get_env_variable(data->env, data->input);
				ft_printf("You entered: %s\n", data->input);
			}
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
	ft_start_minishell(&data);
	return (EXIT_SUCCESS);
}
