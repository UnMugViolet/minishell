/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:24:10 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/11 16:51:20 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_closed_quotes(char *input)
{
	bool in_single_quote = false;
	bool in_double_quote = false;
	int i = 0;

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
	return !(in_single_quote || in_double_quote);
}
