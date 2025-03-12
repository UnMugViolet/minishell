/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:29:05 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/12 11:39:59 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_variable(char **env, char *variable)
{
	int		i;
	size_t	size;
	char	*res;

	i = 0;
	if (!env || !variable)
		return (ft_strdup(""));
	size = ft_strlen(variable) - 1;
	while (env[i])
	{
		if (ft_strncmp(env[i], variable + 1, size) == 0 && env[i][size] == '=')
		{
			res = ft_strdup(env[i] + size + 1);
			return (res);
		}
		i++;
	}
	res = ft_strdup("");
	return (res);
}
