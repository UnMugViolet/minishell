/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:11:18 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/04/02 18:00:05 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_wait_and_update_status(t_data *data)
{
	int i;
	int	status;

	i = 0;
	while (i < data->pid_count)
	{
		if (waitpid(data->pid_list[i], &status, 0) == -1)
			ft_exit_clean(data, ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)));
		ft_update_last_exit_value(data, WEXITSTATUS(status));
		i++;
	}
}

static int	ft_handle_cmd_errors(t_exec *exec)
{
	if (errno == ENOENT)
		return (ft_fprintf(ERR_OUT, CMD_NOT_FOUND, exec->cmd[0]), 127);
	else if (errno == EACCES)
		return (ft_fprintf(ERR_OUT, PERM_DENIED, exec->cmd[0]), 126);
	else
		return (ft_fprintf(2, STDRD_ERR, exec->cmd[0], strerror(errno)), 2);
}

void	ft_exec_child(t_data *data, t_exec *exec, pid_t *pid, int is_pipe)
{
	*pid = fork();
	if (*pid == -1)
		ft_exit_clean(data, ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno)));
	else if (*pid == 0)
	{
		if (exec->in_fd != STDIN_FILENO)
		{
			if (dup2(exec->in_fd, STDIN_FILENO) == -1)
				ft_exit_clean(data, ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)));
			close(exec->in_fd);
		}
		if (exec->out_fd != STDOUT_FILENO)
		{
			if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
				ft_exit_clean(data, ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)));
			close(exec->out_fd);
		}
		if (is_pipe && exec->out_fd == STDOUT_FILENO)
		{
			close (data->pipe_fd[0]);
			if (dup2(data->pipe_fd[1], STDOUT_FILENO) == -1)
				ft_exit_clean(data, ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)));
			close(data->pipe_fd[1]);
		}
		if (execve(exec->full_cmd, exec->cmd, data->env) == -1)
			ft_exit_clean(data, ft_handle_cmd_errors(exec));
	}
	else
	{
		close (data->pipe_fd[0]);
		if (is_pipe && exec->out_fd == STDOUT_FILENO)
			close(data->pipe_fd[1]);
		data->pid_list[data->pid_count++] = *pid;
	}
}

/*
	Handle all the redirections from `>` `<` `>>` `<<` get the file descriptor
	from exec command and redirect the output/input to the file.
	This function is called everytime and executed only if the `type` is 
	`RIGHT_BRACKET` or `LEFT_BRACKET`.
	@param t_exec*exec
	@return void
*/
void	ft_handle_redirection(t_exec *exec)
{
	int	fd;

	if (exec->type == RIGHT_BRACKET)
	{
		fd = open(exec->cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno));
		exec->next->out_fd = fd;
	}
	else if (exec->type == LEFT_BRACKET)
	{
		
		fd = open(exec->cmd[1], O_RDONLY);
		if (fd == -1)
			ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno));
		exec->next->in_fd = fd;
	}
}

