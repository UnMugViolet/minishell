/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:12:15 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/03 10:52:55 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Executes the command in the child process. In case of pipe, creates a pipe.
	and use the `data->pipe_fd` to store the file descriptors.
	@param t_data*data
	@param t_exec*exec
	@param pid_t*pid
	@return void
*/
static void	ft_exec_command(t_data *data, t_exec *exec, int is_pipe, pid_t *pid)
{
	if (is_pipe)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno));
			return ;
		}
	}
	ft_exec_child(data, exec, pid, is_pipe);
	if (is_pipe)
	{
		close(data->pipe_fd[1]);
		if (dup2(data->pipe_fd[0], STDIN_FILENO) == -1)
		{
			ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno));
			return ;
		}
		close(data->pipe_fd[0]);
	}
}

void	ft_execute_prompt(t_data *data)
{
	pid_t	pid;
	t_exec	*tmp;

	tmp = data->exec;
	while (tmp)
	{
		ft_handle_redirection(tmp);
		if (ft_check_exec_builtins(data, tmp->cmd))
			;
		else if (!ft_is_metacharset(tmp->cmd[0], data->metachar))
		{
			if (tmp->next && tmp->next->type == PIPE)
			{
				ft_exec_command(data, tmp, true, &pid);
				tmp = tmp->next;
			}
			else
				ft_exec_command(data, tmp, false, &pid);
		}
		tmp = tmp->next;
	}
	ft_wait_and_update_status(data);
	dup2(data->og_stdin, STDIN_FILENO);
	dup2(data->og_stdout, STDOUT_FILENO);
}
