/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:12:15 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/01 16:33:14 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_command(t_data *data, t_exec *exec, int is_pipe)
{
	pid_t	pid;
	int		status;

	if (is_pipe && pipe(data->pipe_fd) == -1)
	{
		ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno));
		return ;
	}
	ft_exec_child(data, exec, &pid);
	if (!exec->next)
	{
		waitpid(pid, &status, 0);
		ft_update_last_exit_value(data, WEXITSTATUS(status));
	}
	else
		wait(NULL);
}

void	ft_execute_prompt(t_data *data)
{
	t_exec	*tmp;

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
			{
				ft_exec_command(data, tmp, true);
				tmp = tmp->next;
			}
			else
				ft_exec_command(data, tmp, false);
		}
		tmp = tmp->next;
	}
}
