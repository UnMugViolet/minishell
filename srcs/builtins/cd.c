/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:00 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/26 16:06:21 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_update_env_and_free(t_data *data, char *curr_dir, char *new_dir)
{
	ft_update_env_var(data, "PWD", new_dir);
	ft_update_env_var(data, "OLDPWD", curr_dir);
	free(curr_dir);
	free(new_dir);
}

static int	ft_change_dir(t_data *data, char *path)
{
	bool	is_env_var;
	char	*curr_dir;
	char	*new_dir;

	new_dir = path;
	is_env_var = false;
	curr_dir = getcwd(NULL, 0);
	if (!curr_dir)
		return (perror("cd"), 1);
	if (!ft_strncmp(path, "-", 2))
	{
		new_dir = ft_get_associated_env_value(data, "OLDPWD");
		is_env_var = true;
	}
	if (!ft_strncmp(path, "~", 2))
	{
		new_dir = ft_get_associated_env_value(data, "HOME");
		is_env_var = true;
	}
	if (chdir(new_dir) == -1)
		return (perror("cd"), 1);
	if (is_env_var)
		free(new_dir);
	new_dir = getcwd(NULL, 0);
	return (ft_update_env_and_free(data, curr_dir, new_dir), 0);
}

int	ft_cd(t_data *data, char **cmd)
{
	char		*path;
	struct stat	sb;

	ft_print_array_str_fd(cmd, STDOUT_FILENO);
	if (!cmd[1])
	{
		path = ft_get_associated_env_value(data, "HOME");
		if (ft_strlen(path) == 0)
			return (free(path), ft_putstr_fd("cd: HOME not set\n",
					STDERR_FILENO), 1);
		return (ft_change_dir(data, path), free(path), 0);
	}
	else
		path = cmd[1];
	if (cmd[1] && cmd[2])
		return (ft_putstr_fd("cd: Too many arguments\n", STDERR_FILENO), 1);
	else if (stat(path, &sb) == -1 && ft_strncmp(path, "-", 2)
		&& ft_strncmp(path, "~", 2))
		return (perror("cd"), 1);
	else
		return (ft_change_dir(data, path));
}
