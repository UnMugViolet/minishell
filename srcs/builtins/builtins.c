/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:00 by fureimu           #+#    #+#             */
/*   Updated: 2025/04/07 12:57:33 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_export(char **env, char *str, int fd)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		ft_putstr_fd(str, fd);
		ft_putendl_fd(env[i], fd);
		i++;
	}
}


static int	ft_check_exec_builtins(t_data *data, char **cmd)
{
	if (!ft_strncmp(*cmd, "pwd", 4))
		return (ft_putendl_fd(ft_get_env_var_adress(data, "PWD") + 4,
				STDOUT_FILENO), ft_update_last_exit_value(data, 0), 1);
	else if (!ft_strncmp(*cmd, "echo", 5))
		return (ft_echo(cmd), ft_update_last_exit_value(data, 0),  1);
	else if (!ft_strncmp(*cmd, "cd", 3))
		return (ft_update_last_exit_value(data, ft_cd(data, cmd)), 1);
	else if (!ft_strncmp(*cmd, "env", 4) && !cmd[1])
		return (ft_print_array_str_fd(data->env, STDOUT_FILENO),
				ft_update_last_exit_value(data, 0), 1);
	else if (!ft_strncmp(*cmd, "export", 7) && cmd[1])
		return (ft_update_last_exit_value(data, ft_create_env_var(data, cmd[1])), 1);
	else if (!ft_strncmp(*cmd, "export", 7))
		return (ft_print_export(data->env, "export ", STDOUT_FILENO),
				ft_update_last_exit_value(data, 0),  1);
	else if (!ft_strncmp(*cmd, "unset", 6) && cmd[1])
		return (ft_delete_env_var(data, cmd[1]),
				ft_update_last_exit_value(data, 0), 1);
	else if (!ft_strncmp(*cmd, "exit", 5))
		return (ft_exit(data, cmd), 1);
	return (0);
}

/*
	Builtins are commands that are built into the shell. The shell must interpret
	them and display the result. That command is called in the child process
	and will be executed there. The check if the command is a builtin is done
	in the `ft_exec_child` function.
	The builtins are: `pwd` `env` `unset` `exit` `export` `echo -n` `cd`
	@param t_data*data
	@param char*str
	@return void
*/
bool	ft_exec_builtins(t_data *data, t_exec *exec, int is_pipe)
{
	int	save_fd[2];
	
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	if (exec->in_fd != STDIN_FILENO)
		ft_dup(data, exec->in_fd, STDIN_FILENO);
	if (exec->out_fd != STDOUT_FILENO)
		ft_dup(data, exec->out_fd, STDOUT_FILENO);
	if (is_pipe && exec->out_fd == STDOUT_FILENO)
	{
		close(data->pipe_fd[0]);
		ft_dup(data, data->pipe_fd[1], STDOUT_FILENO);
	}
	ft_check_exec_builtins(data, exec->cmd);
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	return (1);
}
