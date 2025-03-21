/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:00:12 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/21 18:40:18 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lex_del_content(t_lex *lex)
{
	if (lex)
	{
		if (lex->content)
			free(lex->content);
		lex->content = ft_strdup("");
	}
}

// TODO: remove for final version debug only
void	ft_print_lex(t_lex *lex)
{
	while (lex)
	{
		printf("type: %zu content: %s\n", lex->type, lex->content);
		lex = lex->next;
	}
}

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
