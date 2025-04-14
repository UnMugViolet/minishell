/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:33:29 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/04/14 11:27:27 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fds(t_data *data)
{
	t_exec	*tmp;

	tmp = data->exec;
	while (tmp)
	{
		if (tmp->in_fd != STDIN_FILENO)
		{
			close(tmp->in_fd);
			tmp->in_fd = STDIN_FILENO;
		}
		if (tmp->out_fd != STDOUT_FILENO)
		{
			close(tmp->out_fd);
			tmp->out_fd = STDOUT_FILENO;
		}
		tmp = tmp->next;
	}
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (data->pipe_fd[1] != -1)
		close(data->pipe_fd[1]);
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
}

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
void	ft_exit_clean(t_data *data, int error_code, bool write)
{
	ft_close_fds(data);
	ft_free_array_str(data->env);
	ft_free_array_str(data->paths);
	ft_free_array_str(data->metachar);
	ft_conditional_free(data->prompt, free);
	ft_conditional_free(data->curr_dir, free);
	ft_conditional_free(data->lex, (void (*)(void *))ft_free_lex);
	ft_conditional_free(data->exec, (void (*)(void *))ft_free_exec);
	ft_conditional_free(data->last_exit_value, free);
	rl_clear_history();
	if (write)
		ft_fprintf(1, "exit\n");
	close(data->og_stdin);
	close(data->og_stdout);
	exit(error_code);
}

void	ft_exit_error(t_data *data, char *str, int code)
{
	ft_fprintf(ERR_OUT, "%s\n", str);
	ft_exit_clean(data, code, false);
}

/*
	Display the usage of the program
	@return void
*/
void	display_usage(void)
{
	ft_printf("Usage: ./minishell\n");
}
