/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:24:44 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/21 09:49:25 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_first_command(t_data *data, size_t *i)
{
	*i = 1;
	ft_print_lex(data->lex);
	while (*i < data->lex_size)
	{
		if (data->lex->type == WORD && !ft_is_env_var(data->lex->content))
			break ;
		data->lex = data->lex->next;
		(*i)++;
	}
}
