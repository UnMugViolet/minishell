/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:29 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/10 18:57:29 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_clean(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->metachar)
		ft_free_array_str(data->metachar);
	rl_clear_history();
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

void	display_usage(void)
{
	ft_printf("Usage: ./minishell\n");
}
