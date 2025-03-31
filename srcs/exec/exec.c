/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:12:15 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/31 13:30:46 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_command(t_data *data, t_exec *exec, int is_pipe)
{
	pid_t	pid;

	if (is_pipe && pipe(data->pipe_fd) == -1)
	{
		ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno));
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		ft_setup_pipe(data, is_pipe, 1);
		ft_exec_child(data, exec);
	}
	else if (pid < 0)
		ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno));
	else
	{
		ft_setup_pipe(data, is_pipe, 0);
		ft_wait_and_update_status(data, pid);
	}
}

static void	ft_exec_and_skip(t_data *data, t_exec *tmp, int is_pipe)
{
	ft_exec_command(data, tmp, is_pipe);
	tmp = tmp->next;
}

void	ft_execute_prompt(t_data *data)
{
	t_exec	*tmp;

	data->in_fd = dup(STDIN_FILENO);
	data->out_fd = dup(STDOUT_FILENO);
	tmp = data->exec;
	while (tmp)
	{
		if (ft_check_exec_builtins(data, tmp->cmd))
			;
		else if (ft_handle_redirection(tmp) == -1)
			ft_exit_error(data, "Error: redirection", 1);
		else if (!ft_is_metacharset(tmp->cmd[0], data->metachar))
		{
			if (tmp->next && tmp->next->type == PIPE)
				ft_exec_and_skip(data, tmp, true);
			else
				ft_exec_command(data, tmp, false);
		}
		tmp = tmp->next;
	}
	dup2(data->in_fd, STDIN_FILENO);
	dup2(data->out_fd, STDOUT_FILENO);
}
