/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:00 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/25 17:05:00 by unmugviolet      ###   ########.fr       */
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

int	ft_echo(char **cmd)
{
	int		i;
	bool	newline;

	newline = true;
	i = 1;
	if (!ft_strncmp(cmd[1], "-n", 3))
	{
		newline = false;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

/*
	Builtins are commands that are built into the shell. The shell must interpret
	them and display the result.
	If the cmd is not a builtin nothing is triggered.
	The builtins are: `pwd` `env` `unset` `exit` `export` `echo -n`
	@param t_data*data
	@param char*str
	@return void
*/
void	ft_exec_builtins(t_data *data, char **cmd)
{
	if (!ft_strncmp(*cmd, "pwd", 4) && !cmd[1])
		ft_putendl_fd(ft_get_env_var_adress(data, "PWD") + 4, STDOUT_FILENO);
	else if (!ft_strncmp(*cmd, "echo", 5))
		ft_echo(cmd);
	else if (!ft_strncmp(*cmd, "cd", 3))
		ft_cd(data, cmd);
	else if (!ft_strncmp(*cmd, "env", 4) && !cmd[1])
		ft_print_array_str_fd(data->env, STDOUT_FILENO);
	else if (!ft_strncmp(*cmd, "export", 7) && cmd[1])
		ft_create_env_var(data, cmd[1]);
	else if (!ft_strncmp(*cmd, "export", 7))
		ft_print_export(data->env, "export ", STDOUT_FILENO);
	else if (!ft_strncmp(*cmd, "unset", 6) && cmd[1])
		ft_delete_env_var(data, cmd[1]);
	else if (!ft_strncmp(data->prompt, "exit", 5))
		ft_exit_clean(data, 1);
	else
		return ;
}
