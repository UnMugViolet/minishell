/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:34 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/13 17:14:13 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_get_path_from_env(t_data *data)
{
	int		i;
	char	**paths;

	i = 0;
	if (*data->env)
	{
		while (ft_strncmp(data->env[i], "PATH=", 5))
			i++;
		paths = ft_split(data->env[i] + 5, ':');
	}
	else
		paths = ft_split(DEF_PATH, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin_free(paths[i], "/");
	return (paths);
}

void	ft_init_data_struct(t_data *data)
{
	data->env = ft_get_path_from_env(data);
	data->prompt = NULL;
	data->lex = NULL;
	data->metachar = ft_split(METACHAR, ' ');
}
