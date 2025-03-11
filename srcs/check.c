/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:24:10 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/11 17:58:18 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_closed_quotes(char *input)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;

	i = 0;
	in_single_quote = false;
	in_double_quote = false;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
		}
		if (input[i] == '\"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
		}
		i++;
	}
	return (!(in_single_quote || in_double_quote));
}

int	ft_is_token(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (data->metachar[i])
	{
		if (ft_strncmp(str, data->metachar[i], ft_strlen(data->metachar[i])))
			return (1);
		i++;
	}
	return (0);
}