/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:29 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/13 18:36:27 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Exit the program and free all the variables that has been malloced
	@param t_data *data
	@return void
*/
void	ft_exit_clean(t_data *data)
{
	if (data->prompt)
		free(data->prompt);
	if (data->metachar)
		ft_free_array_str(data->metachar);
	if (data->lex)
		ft_free_lex(data->lex);
	if (data->paths)
		ft_free_array_str(data->paths);
	rl_clear_history();
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}
/* 
	Display the usage of the program
	@return void
*/
void	display_usage(void)
{
	ft_printf("Usage: ./minishell\n");
}
