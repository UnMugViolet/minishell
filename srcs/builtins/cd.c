/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:00 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/25 16:16:59 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_relative(t_data *data, char *str)
{
}

static int	ft_absolute(t_data *data, char *str)
{
}

int	ft_cd(t_data *data, char **cmd)
{
	int		i;
	char	*path;

	if (!cmd[1])
	{
		path = ft_get_associated_env_value(data, "HOME");
		if (ft_strlen(path) == 0)
			return (ft_putstr_fd("cd: HOME not set", STDERR_FILENO), 1);
	}
	else
		path = cmd[1];
	if (cmd[2])
		return (ft_putstr_fd("cd: Too many arguments", STDERR_FILENO), 1);
	if (cmd[1][0] == '/')
		return (ft_absolute(data, cmd[1]));
	else
		return (ft_relative(data, cmd[1]));
}
