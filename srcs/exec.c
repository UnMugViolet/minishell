/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:12:15 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/27 12:36:54 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_errors(t_exec *exec)
{
	if (errno == ENOENT)
		return (ft_fprintf(2, "minishell: %s: command not found\n",
				exec->cmd[0]), 127);
	else if (errno == EACCES)
		return (ft_fprintf(2, "minishell: %s: permission denied\n",
				exec->cmd[0]), 126);
	else
		return (ft_fprintf(2, "minishell: %s: %s\n", exec->cmd[0],
				strerror(errno)), 2);
}

static void	ft_exec_cmd(t_data *data, t_exec *exec)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(exec->full_cmd, exec->cmd, data->env) == -1)
			exit(ft_handle_errors(exec));
	}
	else if (pid < 0)
		ft_fprintf(2, "minishell: %s\n", strerror(errno));
	else
		waitpid(pid, &status, 0);
}

void	ft_execute_prompt(t_data *data)
{
	t_exec	*tmp;

	tmp = data->exec;
	while (tmp)
	{
		if (ft_check_exec_builtins(data, tmp->cmd))
			;
		else
			ft_exec_cmd(data, tmp);
		tmp = tmp->next;
	}
}
