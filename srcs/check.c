/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:24:10 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/11 00:00:02 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_closed_quotes(char *input)
{
	bool	open_close;
	int		single_double;
	int		i;

	i = -1;
	single_double = 0;
	open_close = false;
	while (input[++i])
	{
		if (input[i] == '\'' && open_close == false)
		{
			open_close = true;
			single_double = 1;
		}
		if (input[i] == '\"' && open_close == false)
		{
			open_close = true;
			single_double = 2;
		}
		if (input[i] == '\'' && open_close == true && single_double == 1)
			open_close = false;
		if (input[i] == '\"' && open_close == true && single_double == 2)
			open_close = false;
	}
	return (!open_close);
}

/* // version gpt le batard
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

	// Returns true if no open quotes are left, meaning they are properly closed
	return !(in_single_quote || in_double_quote);
} */