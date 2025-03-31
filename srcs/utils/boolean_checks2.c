/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:39:26 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/31 10:36:21 by unmugviolet      ###   ########.fr       */
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

static bool	ft_double_token(t_lex *lex, char **metachar)
{
	while (lex)
	{
		if (lex->next && ft_is_metacharset(lex->content, metachar)
			&& ft_is_metacharset(lex->next->content, metachar))
			return (ft_fprintf(ERR_OUT, SYNTAX_ERROR, lex->next->content,
					true));
		lex = lex->next;
	}
	return (false);
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

static bool	ft_word_after_redir(t_lex *lex)
{
	char	**redir_charset;

	redir_charset = ft_split("<< < >> >", ' ');
	while (lex)
	{
		if (ft_is_metacharset(lex->content, redir_charset) && (!lex->next
				|| ft_is_only_whitespace(lex->next->content)))
			return (ft_free_array_str(redir_charset), ft_fprintf(ERR_OUT,
					SYNTAX_ERROR_N), false);
		else if (!ft_strncmp(lex->content, "|", 2) && (!lex->next
				|| ft_is_only_whitespace(lex->next->content)))
			return (ft_free_array_str(redir_charset), ft_fprintf(ERR_OUT,
					SYNTAX_ERROR, " |"), false);
		lex = lex->next;
	}
	return (ft_free_array_str(redir_charset), true);
}

bool	ft_is_correct_token(t_lex *lex, char **metachar)
{
	if (ft_double_token(lex, metachar))
		return (false);
	if (!ft_word_after_redir(lex))
		return (false);
	return (true);
}
