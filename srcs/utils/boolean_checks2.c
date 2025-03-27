/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:39:26 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/27 11:46:18 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_metacharset(char *str, char **metacharset)
{
	int	i;

	i = 0;
	while (metacharset[i])
	{
		if (!ft_strncmp(str, metacharset[i], ft_strlen(metacharset[i])))
			return (true);
		i++;
	}
	return (false);
}

char	*ft_single_token(t_lex *lex, char **metachar)
{
	while (lex)
	{
		if (lex->next && ft_is_metacharset(lex->content, metachar)
			&& ft_is_metacharset(lex->next->content, metachar))
			return (lex->next->content);
		lex = lex->next;
	}
	return (NULL);
}

static bool	ft_is_only_whitespace(char *str)
{
	while (*str)
	{
		if (!ft_is_whitespace(*str))
			return (false);
	}
	return (true);
}

bool	ft_word_after_redir(t_lex *lex)
{
	char	**redir_charset;

	redir_charset = ft_split("<< < >> >", ' ');
	while (lex)
	{
		if (ft_is_metacharset(lex->content, redir_charset)
			&& (!lex->next || ft_is_only_whitespace(lex->next->content)))
			return (false);
		lex = lex->next;
	}
	return (true);
}
