/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_substitute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguinio <yguinio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:16:17 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/17 17:32:07 by yguinio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_str_substitute(char *str, char **env)
{
	char	*var_name;
	char	*env_value;
	char	*res;
	char	*start;
	size_t	var_size;

	start = str;
	var_name = ft_get_env_var_name(str);
	if (!var_name)
		return (str);
	res = ft_substr(str, 0, (ft_strchr(str, '$') - str));
	while (var_name)
	{
		var_size = ft_strlen(var_name) + 1;
		env_value = ft_get_associated_env_value(env, var_name);
		res = ft_strjoin_free(res, env_value);
		str = ft_strchr(str, '$') + var_size;
		res = ft_strjoin_free(res, str);
		var_name = ft_get_env_var_name(str + ft_strlen(var_name + 1));
	}
	free(start);
	return (res);
}
