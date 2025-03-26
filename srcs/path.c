/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 14:18:56 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/26 16:20:42 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Parse the paths given from the `data` struc and return the concatenation of
	the path and the `cmd`.
	If the `cmd` is given with a path (e.g. /bin/ls),
		return the `cmd` if accessed.
	@param t_data *data
	@param char* cmd
	@return char *full_cmd or NULL
*/
char	*ft_get_path_for_cmd(t_data *data, char *cmd)
{
	size_t	i;
	char	*full_cmd;

	i = 0;
	full_cmd = NULL;
	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	else
	{
		while (data->paths[i])
		{
			full_cmd = ft_strjoin(data->paths[i], cmd);
			if (!full_cmd)
				return (ft_exit_error(data, "Error: malloc failed, \
cannot get path for cmd."), NULL);
			if (access(full_cmd, X_OK) == 0)
				return (full_cmd);
			free(full_cmd);
			i++;
		}
	}
	return (NULL);
}
