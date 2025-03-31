/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:11:18 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/31 11:14:08 by unmugviolet      ###   ########.fr       */
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

void	ft_exec_child(t_data *data, t_exec *exec)
{
    if (execve(exec->full_cmd, exec->cmd, data->env) == -1)
        ft_exit_clean(data, ft_handle_cmd_errors(exec));
}

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

void	ft_wait_and_update_status(t_data *data, pid_t pid)
{
    int	status;

    waitpid(pid, &status, 0);
    ft_update_last_exit_value(data, WEXITSTATUS(status));
}
