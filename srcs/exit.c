/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:29 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/13 18:26:16 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_clean(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->metachar)
		ft_free_array_str(data->metachar);
	if (data->lex)
		ft_free_lex(data->lex);
	if (data->env)
		ft_free_array_str(data->env);
	if (data->paths)
		ft_free_array_str(data->paths);
	rl_clear_history();
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

void	display_usage(void)
{
	ft_printf("Usage: ./minishell\n");
}
