/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_substitute.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:16:17 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/24 17:38:31 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Concatenate the `src` string until it finds a `$` to the `dest` string.
	@param char*src
	@param char*dest
	@return char *
*/
static char	*ft_concat_until_next_dollar(char *src, char *dest)
{
	char	*res;
	char	*temp;

	if (!dest && !(*src))
		return (ft_strdup(src));
	temp = ft_substr(src, 0, (ft_strchr(src, '$') - src));
	res = ft_strjoin(dest, temp);
	free(dest);
	free(temp);
	return (res);
}

/*
	Substitute the `$variable` by their value inside the `env` array
	in the string `str`
	@param char*str
	@param t_data*data
	@return char *
*/
char	*ft_str_substitute(char *str, t_data *data)
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
		env_value = ft_get_associated_env_value(data, var_name);
		res = ft_strjoin_free(res, env_value);
		str = ft_strchr(str, '$') + var_size;
		res = ft_concat_until_next_dollar(str, res);
		free(var_name);
		free(env_value);
		var_name = ft_get_env_var_name(str);
	}
	free(start);
	return (res);
}
