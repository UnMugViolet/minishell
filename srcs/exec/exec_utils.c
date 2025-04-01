/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:11:18 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/04/01 16:31:34 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_cmd_errors(t_exec *exec)
{
	if (errno == ENOENT)
		return (ft_fprintf(ERR_OUT, CMD_NOT_FOUND, exec->cmd[0]), 127);
	else if (errno == EACCES)
		return (ft_fprintf(ERR_OUT, PERM_DENIED, exec->cmd[0]), 126);
	else
		return (ft_fprintf(2, STDRD_ERR, exec->cmd[0], strerror(errno)), 2);
}

void	ft_exec_child(t_data *data, t_exec *exec, pid_t *pid)
{
	*pid = fork();
	if (*pid == -1)
		ft_exit_clean(data, ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno)));
	if (*pid == 0)
	{
		if (exec->in_fd != -1)
			if (dup2(exec->in_fd, STDIN_FILENO) == -1)
				ft_exit_clean(data, ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)));
		if (exec->out_fd != -1)
			if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
				ft_exit_clean(data, ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)));
		if (execve(exec->full_cmd, exec->cmd, data->env) == -1)
			ft_exit_clean(data, ft_handle_cmd_errors(exec));
	}
	
}

int	ft_handle_redirection(t_exec *exec)
{
	int	fd;

	if (exec->type == RIGHT_BRACKET)
	{
		fd = open(exec->cmd[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			return (ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)), -1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (exec->type == LEFT_BRACKET)
	{
		fd = open(exec->cmd[1], O_RDONLY);
		if (fd == -1)
			return (ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno)), -1);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	return (0);
}

/*
	Setup the pipe depending on the environment, the pipe 
*/
void	ft_setup_pipe(t_data *data, int is_pipe, int is_child)
{
	if (is_pipe)
	{
		if (is_child)
		{
			close(data->pipe_fd[0]);
			dup2(data->pipe_fd[1], STDOUT_FILENO);
			close(data->pipe_fd[1]);
		}
		else
		{
			close(data->pipe_fd[1]);
			dup2(data->pipe_fd[0], STDIN_FILENO);
			close(data->pipe_fd[0]);
		}
	}
}

