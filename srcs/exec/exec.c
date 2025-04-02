/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:12:15 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/02 12:23:48 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_exec_command(t_data *data, t_exec *exec, int is_pipe, pid_t *pid)
{
	if (is_pipe && pipe(data->pipe_fd) == -1)
	{
		ft_fprintf(2, STDRD_ERR_SINGLE, strerror(errno));
		return ;
	}
	ft_exec_child(data, exec, pid);
}

void	ft_execute_prompt(t_data *data)
{
	pid_t	pid;
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
				ft_exec_command(data, tmp, true, &pid);
				tmp = tmp->next;
			}
			else
				ft_exec_command(data, tmp, false, &pid);
		}
		tmp = tmp->next;
	}
	ft_wait_and_update_status(data);
}
