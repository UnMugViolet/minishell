/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:24:10 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/12 11:19:15 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_closed_quotes(char *prompt)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;

	i = -1;
	in_single_quote = false;
	in_double_quote = false;
	while (prompt[++i])
	{
		if (prompt[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		if (prompt[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
	}
	return (!(in_single_quote || in_double_quote));
}

bool	ft_is_token(char *str, t_data *data)
{
	int	i;

	i = -1;
	while (data->metachar[++i])
		if (ft_strncmp(str, data->metachar[i], ft_strlen(data->metachar[i])))
			return (true);
	return (false);
}
