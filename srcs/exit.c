/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:29 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/21 11:49:22 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Free the given `ptr` if not `NULL`
	@param void*ptr
	@return void
*/
static void	ft_conditional_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

/*
	Exit the program and free all the variables that has been malloced
	@param t_data *data
	@return void
*/
void	ft_exit_clean(t_data *data)
{
	ft_free_array_str(data->paths);
	ft_free_array_str(data->metachar);
	ft_free_array_str(data->env);
	ft_conditional_free(data->prompt);
	ft_conditional_free(data->lex);
	ft_conditional_free(data->last_exit_value);
	if (data->exec)
		ft_free_array_str(data->exec->cmd);
	rl_clear_history();
	ft_fprintf(1, "exit\n");
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
