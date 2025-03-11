/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:34 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/11 16:24:37 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_path_from_env(t_data *data)
{
	int	i;

	i = 0;
	if (*data->env)
	{
		while (ft_strncmp(data->env[i], "PATH=", 5))
		i++;
		data->paths = ft_split(data->env[i] + 5, ':');
	}
	else
		data->paths = ft_split("/usr/local/sbin:/usr/local/bin:/usr/sbin:\
/usr/bin:/sbin:/bin", ':');
	i = -1;
	while (data->paths[++i])
		data->paths[i] = ft_strjoin_free(data->paths[i], "/");
	ft_print_array_str_fd(data->paths, 1);
}
