/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:24:45 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/17 12:34:09 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_first_command(t_data *data, int *i)
{
	*i = 0;
	if (data->lex->type == WORD)
		return ;
	else if (data->lex->type == DOUBLE_LEFT_BRACKET)
		*i = 1;
	else
		ft_printf("Symbol found, TODO implement\n");
}
