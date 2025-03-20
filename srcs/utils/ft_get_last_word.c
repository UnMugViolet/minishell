/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_last_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:50:36 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/20 15:26:12 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Returns the content of the last `word` element in the `lex` linked list.
	Returns `NULL` if no word in the `lex` linked list.
	@param t_lex*lex
	@return char *
*/
char	*ft_get_last_word(t_lex *lex)
{
	char	*last;

	last = NULL;
	while (lex)
	{
		if (lex->type == WORD)
			last = lex->content;
		lex = lex->next;
	}
	return (last);
}
