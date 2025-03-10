/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:38:07 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/10 18:32:24 by fureimu          ###   ########.fr       */
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
	for (int i = 0; data->metachar[i]; i++)
		ft_printf("%s\n", data->metachar[i]);
	while (true)
	{
		data->input = readline(CLR_BLUE "minishell> " CLR_RESET);
		if (data->input && *data->input == '\0')
			continue ;
		else if (data->input)
		{
			ft_printf("You entered: %s\n", data->input);
			add_history(data->input);
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
	(void)env;
	ft_setup_signals();
	ft_start_minishell(&data);
	return (EXIT_SUCCESS);
}
