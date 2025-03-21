/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:24:44 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/21 14:01:10 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_first_command_index(t_data *data, size_t *i)
{
	*i = 0;
	ft_print_lex(data->lex);
	while (*i < data->lex_size)
	{
		if (data->lex->type == WORD)
			break ;
		data->lex = data->lex->next;
		(*i)++;
	}
}
