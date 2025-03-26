/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:29 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/26 11:07:57 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Free the given `ptr` if not `NULL`
	@param void*ptr
	@return void
*/
static void	ft_conditional_free(void *ptr, void (*func)(void *))
{
	if (ptr)
		func(ptr);
}

/*
	Exit the program and free all the variables that has been malloced
	@param t_data *data
	@return void
*/
void	ft_exit_clean(t_data *data, bool write_exit)
{
    ft_free_array_str(data->paths);
    ft_free_array_str(data->metachar);
    ft_free_array_str(data->env);
    ft_conditional_free(data->prompt, free);
    ft_conditional_free(data->curr_dir, free);
    ft_conditional_free(data->lex, (void (*)(void *))ft_free_lex);
    ft_conditional_free(data->exec, (void (*)(void *))ft_free_exec);
    ft_conditional_free(data->last_exit_value, free);
    rl_clear_history(); 
	if (write_exit)
    	ft_fprintf(1, "exit\n");
    exit(EXIT_SUCCESS);
}

void	ft_exit_error(t_data *data, char *str)
{
	ft_fprintf(STDERR_FILENO, "%s\n", str);
	ft_exit_clean(data, 0);
	exit(EXIT_FAILURE);
}

/*
	Display the usage of the program
	@return void
*/
void	display_usage(void)
{
	ft_printf("Usage: ./minishell\n");
}
