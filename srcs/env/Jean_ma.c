/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skibidi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:58:39 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/14 12:00:42 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_toggle_quotes(char c, bool *in_sgl, bool *in_dbl)
{
	if (c == '\'' && !*in_dbl)
		*in_sgl =! *in_sgl;
	if (c == '"' && !*in_sgl)
		*in_dbl =! *in_dbl;
}
